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

To complete this tutorial, I focused on completing the available tutorial or assignment workflow and organising its technical and written evidence. I reviewed the available files and outputs together so that the implementation, written explanation, and supporting evidence remained connected to the task objectives. Where the evidence did not clearly describe a personal contribution, I kept the description limited to the work that can be verified from this folder.

## Key Learning Outcomes

I learned how Python orchestration, a local analytical database, dbt models, data-quality checks, and reporting outputs can form a structured data pipeline.

The work also strengthened my understanding of cloud data engineering, distributed processing, artificial intelligence, analytical pipelines, academic writing, and technical communication. I became more aware that a technical result should be supported by a clear process, suitable evidence, and an explanation of why the selected approach was appropriate. This will help me approach related tasks more systematically in future coursework.

## Reflection

The tutorial made the difference between a one-off analysis and a repeatable pipeline clearer. File organisation, schema checks, model dependencies, and reproducible outputs were as important as the final charts.

The most important challenge was connecting several tools and processing stages while keeping paths, formats, configurations, and explanations consistent. Working through this required me to check the task in smaller stages and compare the result with the available requirements or evidence. This process improved my patience and made me more careful about verifying technical work before presenting it.

Overall, this tutorial contributed to my development by combining practical work with documentation and reflection. It showed me which parts I can now complete with more confidence and which areas still require further practice. The experience will be useful when I work on larger projects that demand clearer organisation, stronger testing, and more independent technical decisions.

## Possible Improvements

Move credentials and environment-specific settings outside tracked configuration. A useful next step would be to add dbt tests and Python unit tests. A useful next step would be to add automated scheduling and pipeline-run logging.

In a future version, I would also focus on reproducible setup instructions, architecture diagrams, stronger security practices, validation evidence, and clearer comparison of alternative approaches. These additions would make the work easier to understand, reproduce, and evaluate while providing stronger evidence of the development process.
