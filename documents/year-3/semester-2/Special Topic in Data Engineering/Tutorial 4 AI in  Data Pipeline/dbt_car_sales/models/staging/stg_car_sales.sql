WITH typed AS (
    SELECT
        TRY_CAST("Date" AS DATE) AS sale_date,
        REGEXP_REPLACE(TRIM(CAST("Salesperson" AS VARCHAR)), '\s+', ' ', 'g') AS salesperson,
        REGEXP_REPLACE(TRIM(CAST("Customer Name" AS VARCHAR)), '\s+', ' ', 'g') AS customer_name,
        REGEXP_REPLACE(TRIM(CAST("Car Make" AS VARCHAR)), '\s+', ' ', 'g') AS car_make,
        REGEXP_REPLACE(TRIM(CAST("Car Model" AS VARCHAR)), '\s+', ' ', 'g') AS car_model,
        TRY_CAST("Car Year" AS INTEGER) AS car_year,
        TRY_CAST(REGEXP_REPLACE(CAST("Sale Price" AS VARCHAR), '[^0-9.-]', '', 'g') AS DOUBLE) AS sale_price,
        TRY_CAST(REGEXP_REPLACE(CAST("Commission Rate" AS VARCHAR), '[^0-9.-]', '', 'g') AS DOUBLE) AS commission_rate,
        TRY_CAST(REGEXP_REPLACE(CAST("Commission Earned" AS VARCHAR), '[^0-9.-]', '', 'g') AS DOUBLE) AS commission_earned
    FROM raw_car_sales
)

SELECT
    sale_date,
    salesperson,
    customer_name,
    car_make,
    car_model,
    car_year,
    sale_price,
    commission_rate,
    commission_earned,
    ROUND(sale_price * commission_rate, 2) AS calculated_commission,
    ROUND(commission_earned - ROUND(sale_price * commission_rate, 2), 2) AS commission_difference,
    EXTRACT(YEAR FROM sale_date)::INTEGER AS year,
    EXTRACT(MONTH FROM sale_date)::INTEGER AS month,
    EXTRACT(QUARTER FROM sale_date)::INTEGER AS quarter,
    STRFTIME(sale_date, '%Y-%m') AS year_month
FROM typed
WHERE sale_date IS NOT NULL
  AND sale_price > 0
  AND commission_rate BETWEEN 0 AND 1
