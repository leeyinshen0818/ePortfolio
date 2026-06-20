SELECT
    salesperson,
    COUNT(*) AS transaction_count,
    ROUND(SUM(sale_price), 2) AS total_sales,
    ROUND(AVG(sale_price), 2) AS average_sale_price,
    ROUND(SUM(commission_earned), 2) AS total_commission,
    ROUND(AVG(commission_rate), 4) AS average_commission_rate,
    MIN(sale_date) AS first_sale_date,
    MAX(sale_date) AS last_sale_date
FROM "car_sales"."main"."stg_car_sales"
GROUP BY salesperson
ORDER BY total_sales DESC