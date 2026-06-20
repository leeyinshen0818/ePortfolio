WITH raw_typed AS (
    SELECT
        TRY_CAST("Date" AS DATE) AS parsed_date,
        TRY_CAST(REGEXP_REPLACE(CAST("Sale Price" AS VARCHAR), '[^0-9.-]', '', 'g') AS DOUBLE) AS parsed_sale_price,
        TRY_CAST(REGEXP_REPLACE(CAST("Commission Rate" AS VARCHAR), '[^0-9.-]', '', 'g') AS DOUBLE) AS parsed_commission_rate
    FROM raw_car_sales
),

counts AS (
    SELECT
        (SELECT COUNT(*) FROM raw_car_sales) AS raw_row_count,
        (SELECT COUNT(*) FROM {{ ref('stg_car_sales') }}) AS cleaned_row_count,
        (SELECT COUNT(*) FROM raw_car_sales)
            - (SELECT COUNT(*) FROM (SELECT DISTINCT * FROM raw_car_sales)) AS duplicate_rows,
        SUM(CASE WHEN parsed_date IS NULL THEN 1 ELSE 0 END) AS invalid_dates,
        SUM(CASE WHEN parsed_sale_price IS NULL OR parsed_sale_price <= 0 THEN 1 ELSE 0 END) AS invalid_sale_price_rows,
        SUM(CASE WHEN parsed_commission_rate IS NULL OR parsed_commission_rate < 0 OR parsed_commission_rate > 1 THEN 1 ELSE 0 END) AS invalid_commission_rate_rows
    FROM raw_typed
),

commission_stats AS (
    SELECT
        MIN(commission_difference) AS commission_difference_min,
        MAX(commission_difference) AS commission_difference_max,
        AVG(commission_difference) AS commission_difference_mean,
        SUM(CASE WHEN ABS(commission_difference) > 0.01 THEN 1 ELSE 0 END) AS commission_difference_non_zero_count
    FROM {{ ref('stg_car_sales') }}
)

SELECT
    counts.raw_row_count,
    counts.cleaned_row_count,
    counts.raw_row_count - counts.cleaned_row_count AS rows_removed,
    counts.duplicate_rows,
    counts.invalid_dates,
    counts.invalid_sale_price_rows,
    counts.invalid_commission_rate_rows,
    ROUND(commission_stats.commission_difference_min, 4) AS commission_difference_min,
    ROUND(commission_stats.commission_difference_max, 4) AS commission_difference_max,
    ROUND(commission_stats.commission_difference_mean, 4) AS commission_difference_mean,
    commission_stats.commission_difference_non_zero_count,
    ROUND(
        commission_stats.commission_difference_non_zero_count * 100.0
        / NULLIF(counts.cleaned_row_count, 0),
        2
    ) AS commission_difference_non_zero_percentage
FROM counts
CROSS JOIN commission_stats
