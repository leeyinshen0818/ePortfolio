from pathlib import Path
from datetime import datetime
import subprocess

import duckdb
import matplotlib
import pandas as pd


matplotlib.use("Agg")
import matplotlib.pyplot as plt

USE_SAMPLE = True
SAMPLE_SIZE = 50000
RANDOM_STATE = 42

PROJECT_ROOT = Path(__file__).resolve().parents[1]
RAW_CSV_PATH = PROJECT_ROOT / "data" / "raw" / "car_sales_data.csv"
PROCESSED_DIR = PROJECT_ROOT / "data" / "processed"
WAREHOUSE_DIR = PROJECT_ROOT / "warehouse"
CHARTS_DIR = PROJECT_ROOT / "charts"
SCREENSHOTS_DIR = PROJECT_ROOT / "screenshots"
DBT_PROJECT_DIR = PROJECT_ROOT / "dbt_car_sales"
DUCKDB_PATH = WAREHOUSE_DIR / "car_sales.duckdb"

REQUIRED_COLUMNS = [
    "Date",
    "Salesperson",
    "Customer Name",
    "Car Make",
    "Car Model",
    "Car Year",
    "Sale Price",
    "Commission Rate",
    "Commission Earned",
]

DBT_TABLES = [
    "stg_car_sales",
    "data_quality_summary",
    "salesperson_metrics",
    "car_make_summary",
    "car_model_summary",
    "monthly_sales_summary",
]

GENERATED_TABLES = ["raw_car_sales", *DBT_TABLES]

CSV_OUTPUTS = {
    "stg_car_sales": PROCESSED_DIR / "cleaned_car_sales.csv",
    "data_quality_summary": PROCESSED_DIR / "data_quality_summary.csv",
    "salesperson_metrics": PROCESSED_DIR / "salesperson_metrics.csv",
    "car_make_summary": PROCESSED_DIR / "car_make_summary.csv",
    "car_model_summary": PROCESSED_DIR / "car_model_summary.csv",
    "monthly_sales_summary": PROCESSED_DIR / "monthly_sales_summary.csv",
}

CHART_OUTPUTS = {
    "sales_by_salesperson": CHARTS_DIR / "sales_by_salesperson.png",
    "sales_by_car_make": CHARTS_DIR / "sales_by_car_make.png",
    "monthly_sales_trend": CHARTS_DIR / "monthly_sales_trend.png",
    "commission_rate_distribution": CHARTS_DIR / "commission_rate_distribution.png",
}


def print_stage(message: str) -> None:
    print(f"\n[{datetime.now().strftime('%H:%M:%S')}] {message}")


def create_folders() -> None:
    print_stage("Setup: creating required folders")
    for folder in [PROCESSED_DIR, WAREHOUSE_DIR, CHARTS_DIR, SCREENSHOTS_DIR]:
        folder.mkdir(parents=True, exist_ok=True)


def validate_input_file() -> None:
    if not RAW_CSV_PATH.exists():
        raise FileNotFoundError(
            f"Missing input CSV: {RAW_CSV_PATH}\n"
            "Place car_sales_data.csv in data/raw/ before running the pipeline."
        )


def validate_required_columns(columns: list[str]) -> None:
    missing_columns = [column for column in REQUIRED_COLUMNS if column not in columns]
    if missing_columns:
        raise ValueError(f"Missing required column(s): {', '.join(missing_columns)}")


def load_raw_csv() -> tuple[pd.DataFrame, int, int]:
    print_stage("Loading raw CSV: reading source data with pandas")
    validate_input_file()

    raw_df = pd.read_csv(RAW_CSV_PATH)
    validate_required_columns(raw_df.columns.tolist())

    full_dataset_row_count = len(raw_df)
    if USE_SAMPLE and full_dataset_row_count > SAMPLE_SIZE:
        raw_df = raw_df.sample(n=SAMPLE_SIZE, random_state=RANDOM_STATE).reset_index(drop=True)
    else:
        raw_df = raw_df.copy()

    sample_size_used = len(raw_df)
    print(f"Full dataset row count: {full_dataset_row_count:,}")
    print(f"Rows selected for this run: {sample_size_used:,}")
    return raw_df, full_dataset_row_count, sample_size_used


def create_raw_table(raw_df: pd.DataFrame) -> None:
    print_stage("Creating raw_car_sales: loading sample into DuckDB")
    conn = duckdb.connect(str(DUCKDB_PATH))
    try:
        conn.register("raw_df", raw_df)
        conn.execute("CREATE OR REPLACE TABLE raw_car_sales AS SELECT * FROM raw_df")
        conn.unregister("raw_df")
        print("Created table: raw_car_sales")
    finally:
        conn.close()
        print("DuckDB connection closed before dbt run")


def run_dbt() -> None:
    print_stage("Running dbt: building staging and mart tables")
    command = ["dbt", "run", "--profiles-dir", "."]
    try:
        result = subprocess.run(
            command,
            cwd=DBT_PROJECT_DIR,
            check=True,
            capture_output=True,
            text=True,
        )
    except FileNotFoundError as error:
        raise RuntimeError(
            "dbt was not found. Install it with: python -m pip install dbt-duckdb"
        ) from error
    except subprocess.CalledProcessError as error:
        print(error.stdout)
        print(error.stderr)
        raise RuntimeError("dbt run failed. Review the dbt output above.") from error

    print(result.stdout)
    print("dbt run completed successfully")


def connect_to_duckdb() -> duckdb.DuckDBPyConnection:
    print_stage("DuckDB connection: reconnecting after dbt run")
    return duckdb.connect(str(DUCKDB_PATH))


def validate_dbt_tables(conn: duckdb.DuckDBPyConnection) -> None:
    existing_tables = {
        row[0]
        for row in conn.execute(
            """
            SELECT table_name
            FROM information_schema.tables
            WHERE table_schema = 'main'
            """
        ).fetchall()
    }
    missing_tables = [table for table in DBT_TABLES if table not in existing_tables]
    if missing_tables:
        raise RuntimeError(f"Missing dbt-created table(s): {', '.join(missing_tables)}")
    print("Verified dbt-created tables are present")


def export_csv_outputs(conn: duckdb.DuckDBPyConnection) -> None:
    print_stage("Exporting CSV outputs: writing processed files")
    for table_name, output_path in CSV_OUTPUTS.items():
        conn.execute(f"COPY {table_name} TO '{output_path.as_posix()}' (HEADER, DELIMITER ',')")
        print(f"Exported: {output_path.relative_to(PROJECT_ROOT)}")


def save_bar_chart(
    df: pd.DataFrame,
    x_column: str,
    y_column: str,
    title: str,
    x_label: str,
    y_label: str,
    output_path: Path,
    color: str,
) -> None:
    plt.figure(figsize=(12, 7))
    plt.bar(df[x_column], df[y_column], color=color)
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.xticks(rotation=45, ha="right")
    plt.tight_layout()
    plt.savefig(output_path, dpi=150)
    plt.close()


def create_charts(conn: duckdb.DuckDBPyConnection) -> None:
    print_stage("Generating charts: creating Matplotlib PNG files")

    salesperson_df = conn.execute(
        """
        SELECT salesperson, total_sales
        FROM salesperson_metrics
        ORDER BY total_sales DESC
        LIMIT 10
        """
    ).fetchdf()
    save_bar_chart(
        salesperson_df,
        "salesperson",
        "total_sales",
        "Top 10 Salespeople by Sales Revenue",
        "Salesperson",
        "Total Sales Revenue",
        CHART_OUTPUTS["sales_by_salesperson"],
        "#2563eb",
    )

    car_make_df = conn.execute(
        """
        SELECT car_make, total_sales
        FROM car_make_summary
        ORDER BY total_sales DESC
        LIMIT 10
        """
    ).fetchdf()
    save_bar_chart(
        car_make_df,
        "car_make",
        "total_sales",
        "Sales Revenue by Car Make",
        "Car Make",
        "Total Sales Revenue",
        CHART_OUTPUTS["sales_by_car_make"],
        "#059669",
    )

    monthly_df = conn.execute(
        """
        SELECT year_month, total_sales, possible_partial_month
        FROM monthly_sales_summary
        ORDER BY year_month
        """
    ).fetchdf()
    plt.figure(figsize=(13, 7))
    plt.plot(monthly_df["year_month"], monthly_df["total_sales"], marker="o", color="#7c3aed")
    for _, row in monthly_df[monthly_df["possible_partial_month"]].iterrows():
        plt.annotate(
            "Possible partial month",
            xy=(row["year_month"], row["total_sales"]),
            xytext=(0, 14),
            textcoords="offset points",
            ha="center",
            fontsize=8,
            arrowprops={"arrowstyle": "->", "lw": 0.8},
        )
    plt.title("Monthly Sales Revenue Trend")
    plt.xlabel("Year-Month")
    plt.ylabel("Total Sales Revenue")
    plt.xticks(rotation=45, ha="right")
    plt.tight_layout()
    plt.savefig(CHART_OUTPUTS["monthly_sales_trend"], dpi=150)
    plt.close()

    commission_df = conn.execute(
        """
        SELECT commission_rate
        FROM stg_car_sales
        WHERE commission_rate IS NOT NULL
        """
    ).fetchdf()
    plt.figure(figsize=(10, 6))
    plt.hist(commission_df["commission_rate"], bins=30, color="#dc2626", edgecolor="white")
    plt.title("Commission Rate Distribution")
    plt.xlabel("Commission Rate")
    plt.ylabel("Transaction Count")
    plt.tight_layout()
    plt.savefig(CHART_OUTPUTS["commission_rate_distribution"], dpi=150)
    plt.close()

    for output_path in CHART_OUTPUTS.values():
        print(f"Created chart: {output_path.relative_to(PROJECT_ROOT)}")


def get_pipeline_metrics(conn: duckdb.DuckDBPyConnection) -> dict:
    quality = conn.execute("SELECT * FROM data_quality_summary").fetchdf().iloc[0].to_dict()
    totals = conn.execute(
        """
        SELECT
            COUNT(*) AS cleaned_row_count,
            ROUND(SUM(sale_price), 2) AS total_sales,
            ROUND(SUM(commission_earned), 2) AS total_commission,
            MIN(sale_date) AS min_sale_date,
            MAX(sale_date) AS max_sale_date,
            COUNT(DISTINCT salesperson) AS unique_salespeople,
            COUNT(DISTINCT car_make) AS unique_car_makes,
            COUNT(DISTINCT car_model) AS unique_car_models
        FROM stg_car_sales
        """
    ).fetchdf().iloc[0].to_dict()
    partial_month_count = conn.execute(
        "SELECT COUNT(*) FROM monthly_sales_summary WHERE possible_partial_month"
    ).fetchone()[0]
    return {**quality, **totals, "partial_month_count": partial_month_count}


def format_file_list(paths: list[Path]) -> str:
    return "\n".join(f"- {path.relative_to(PROJECT_ROOT)}" for path in paths)


def generate_run_summary(
    conn: duckdb.DuckDBPyConnection,
    full_dataset_row_count: int,
    sample_size_used: int,
) -> None:
    print_stage("Generating summary: writing pipeline_run_summary.txt")
    metrics = get_pipeline_metrics(conn)
    summary_path = PROCESSED_DIR / "pipeline_run_summary.txt"
    run_timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    summary = f"""AI Car Sales DuckDB + dbt Pipeline Run Summary

Run timestamp: {run_timestamp}
Status: SUCCESS

Input and warehouse:
- Input CSV path: {RAW_CSV_PATH.relative_to(PROJECT_ROOT)}
- DuckDB database path: {DUCKDB_PATH.relative_to(PROJECT_ROOT)}
- dbt project path: {DBT_PROJECT_DIR.relative_to(PROJECT_ROOT)}
- Full dataset row count: {full_dataset_row_count:,}
- USE_SAMPLE: {USE_SAMPLE}
- Sample size used: {sample_size_used:,}
- Random state: {RANDOM_STATE}

Row counts:
- Cleaned row count: {int(metrics["cleaned_row_count"]):,}
- Rows removed: {int(metrics["rows_removed"]):,}
- Duplicate rows in sample: {int(metrics["duplicate_rows"]):,}

Invalid row summary:
- Invalid dates: {int(metrics["invalid_dates"]):,}
- Invalid sale price rows: {int(metrics["invalid_sale_price_rows"]):,}
- Invalid commission rate rows: {int(metrics["invalid_commission_rate_rows"]):,}

Commission difference summary:
- Minimum difference: {metrics["commission_difference_min"]}
- Maximum difference: {metrics["commission_difference_max"]}
- Mean difference: {metrics["commission_difference_mean"]}
- Non-zero difference count: {int(metrics["commission_difference_non_zero_count"]):,}
- Non-zero difference percentage: {metrics["commission_difference_non_zero_percentage"]}%

Business metrics:
- Total sales revenue: {metrics["total_sales"]}
- Total commission earned: {metrics["total_commission"]}
- Date range: {metrics["min_sale_date"]} to {metrics["max_sale_date"]}
- Unique salespeople: {int(metrics["unique_salespeople"]):,}
- Unique car makes: {int(metrics["unique_car_makes"]):,}
- Unique car models: {int(metrics["unique_car_models"]):,}

Generated DuckDB tables:
{chr(10).join(f"- {table}" for table in GENERATED_TABLES)}

Generated CSV files:
{format_file_list(list(CSV_OUTPUTS.values()))}

Generated chart files:
{format_file_list(list(CHART_OUTPUTS.values()))}

Notes:
- dbt handles the SQL transformation layer after Python loads raw_car_sales.
- Possible partial months are flagged when a monthly transaction count is less than 50% of the median monthly transaction count.
- Possible partial month count: {int(metrics["partial_month_count"]):,}
- Similar sales totals by car make may suggest synthetic, randomized, or intentionally balanced data.
"""
    summary_path.write_text(summary, encoding="utf-8")
    print(f"Created summary: {summary_path.relative_to(PROJECT_ROOT)}")


def run_pipeline() -> None:
    conn = None
    try:
        create_folders()
        raw_df, full_dataset_row_count, sample_size_used = load_raw_csv()
        create_raw_table(raw_df)
        run_dbt()

        conn = connect_to_duckdb()
        validate_dbt_tables(conn)
        export_csv_outputs(conn)
        create_charts(conn)
        generate_run_summary(conn, full_dataset_row_count, sample_size_used)

        print_stage("Pipeline completed successfully")

    except (FileNotFoundError, ValueError, RuntimeError) as error:
        print(f"\nERROR: {error}")
        raise
    except Exception as error:
        print(f"\nPipeline failed with unexpected error: {error}")
        raise
    finally:
        if conn is not None:
            conn.close()
            print("DuckDB connection closed")


if __name__ == "__main__":
    run_pipeline()
