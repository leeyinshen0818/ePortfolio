# Azure Data Engineering Tutorial

## Overview

This tutorial contains a cloud data-engineering workflow using Azure storage, PySpark notebooks, layered bronze/silver/gold data, and Power BI evidence.

## Objectives

- Access data stored in Azure.
- Transform Parquet data and save prepared Delta tables.
- Organise data using bronze, silver, and gold layers.
- Present processed data through Power BI.

## Tools and Technologies

Azure Data Lake Storage paths, PySpark, Databricks-style notebooks, Parquet, Delta Lake, and Power BI.

## Folder Contents / Evidence

| Evidence | Link |
|---|---|
| Tutorial report | [G1_Azure Tutorial.pdf](<G1_Azure Tutorial.pdf>) |
| Notebooks and sample data | [Azure folder](Azure) |
| Power BI files and exports | [PowerBI folder](PowerBI) |

## What I Did

I worked with notebooks that accessed cloud storage, transformed date fields, processed multiple tables, standardised column names, and moved data between data layers. I also retained dashboard evidence for the presentation stage.

## Key Learning Outcomes

I learned how storage, transformation, table formats, and reporting tools connect within a basic data pipeline.

## Reflection

This tutorial was useful because it moved beyond local data analysis into a cloud workflow. The main challenge was managing paths, formats, and access configuration correctly.

## Possible Improvements

- Replace embedded credentials with Azure secrets or managed identities.
- Add a pipeline diagram and reproducible setup instructions.
