
  
    
    

    create  table
      "car_sales"."main"."monthly_sales_summary__dbt_tmp"
  
    as (
      WITH monthly AS (
    SELECT
        year_month,
        ROUND(SUM(sale_price), 2) AS total_sales,
        COUNT(*) AS transaction_count,
        ROUND(AVG(sale_price), 2) AS average_sale_price,
        ROUND(SUM(commission_earned), 2) AS total_commission
    FROM "car_sales"."main"."stg_car_sales"
    GROUP BY year_month
),

with_median AS (
    SELECT
        *,
        MEDIAN(transaction_count) OVER () AS median_monthly_transaction_count
    FROM monthly
)

SELECT
    year_month,
    total_sales,
    transaction_count,
    average_sale_price,
    total_commission,
    median_monthly_transaction_count,
    transaction_count < median_monthly_transaction_count * 0.5 AS possible_partial_month
FROM with_median
ORDER BY year_month
    );
  
  