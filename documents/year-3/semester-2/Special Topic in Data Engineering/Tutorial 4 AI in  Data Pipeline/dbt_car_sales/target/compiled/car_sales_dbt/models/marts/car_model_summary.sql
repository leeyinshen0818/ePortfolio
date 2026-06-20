SELECT
    car_make,
    car_model,
    COUNT(*) AS transaction_count,
    ROUND(SUM(sale_price), 2) AS total_sales,
    ROUND(AVG(sale_price), 2) AS average_sale_price,
    ROUND(SUM(commission_earned), 2) AS total_commission
FROM "car_sales"."main"."stg_car_sales"
GROUP BY car_make, car_model
ORDER BY total_sales DESC