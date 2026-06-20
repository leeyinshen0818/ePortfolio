# Tutorial 4: AI-Assisted Data Pipeline

## Overview

This tutorial builds a car-sales data pipeline with Python, DuckDB, dbt, pandas, and Matplotlib. The pipeline loads raw data, validates its schema, creates staging and mart tables, exports processed datasets, and produces analytical charts.

## Objectives

- Build a repeatable local analytical pipeline.
- Validate required columns and clean data types.
- Use dbt models to separate staging and business marts.
- Store transformed data in DuckDB.
- Export summaries and create charts for reporting.

## Tools and Technologies

- Python and pandas
- DuckDB
- dbt with SQL and YAML models
- Matplotlib
- CSV data
- AI-assisted pipeline development documented in the report

## Folder Contents / Evidence

- [Tutorial report](<Tutorial 4_ Claude to Pipeline.pdf>)
- [Pipeline script](scripts/duckdb_car_sales_pipeline.py)
- [dbt project](dbt_car_sales)
- [Staging model](dbt_car_sales/models/staging/stg_car_sales.sql)
- [Mart models](dbt_car_sales/models/marts)
- [Processed datasets](data/processed)
- [Generated charts](charts)
- [DuckDB warehouse](warehouse/car_sales.duckdb)
- [Raw-data source link](<data/raw/Data source link.txt>)

## What I Did

I organised the pipeline stages, added input and table validation, transformed car-sales records with dbt, exported analytical summaries, and generated charts for sales and commission analysis.

## Key Learning Outcomes

I learned how Python orchestration, a local analytical database, dbt models, data-quality checks, and reporting outputs can form a structured data pipeline.

## Reflection

The tutorial made the difference between a one-off analysis and a repeatable pipeline clearer. File organisation, schema checks, model dependencies, and reproducible outputs were as important as the final charts.

## Possible Improvements

- Move credentials and environment-specific settings outside tracked configuration.
- Add dbt tests and Python unit tests.
- Add automated scheduling and pipeline-run logging.
