
  
    
    

    create  table
      "car_sales"."main"."car_make_summary__dbt_tmp"
  
    as (
      SELECT
    car_make,
    COUNT(*) AS transaction_count,
    ROUND(SUM(sale_price), 2) AS total_sales,
    ROUND(AVG(sale_price), 2) AS average_sale_price,
    ROUND(SUM(commission_earned), 2) AS total_commission,
    MIN(car_year) AS oldest_car_year,
    MAX(car_year) AS newest_car_year
FROM "car_sales"."main"."stg_car_sales"
GROUP BY car_make
ORDER BY total_sales DESC
    );
  
  