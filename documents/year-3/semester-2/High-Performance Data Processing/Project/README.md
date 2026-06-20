# High-Performance Property Data Crawler

## Overview

This project collects Malaysian property-listing data from Mudah, compares a sequential baseline with an asynchronous crawler, and cleans the resulting large dataset with PySpark.

## Objectives

- Build a controlled baseline crawler and record performance metrics.
- Improve throughput using asynchronous requests and bounded concurrency.
- Partition the search space by region and stop when inventory pages are exhausted.
- Clean duplicate or incomplete property records with PySpark.

## Tools and Technologies

- Python
- `requests` and `aiohttp`
- `asyncio`
- `psutil`
- PySpark and pandas
- CSV data

## Folder Contents / Evidence

- [Project source and datasets](Web_Crawler_Project)
- [Baseline crawler](Web_Crawler_Project/mudah_baseline.py)
- [Optimised asynchronous crawler](Web_Crawler_Project/mudah_optimized_async.py)
- [PySpark cleaning pipeline](Web_Crawler_Project/clean_data.py)
- [Cleaned 100K dataset](Web_Crawler_Project/mudah_100k_cleaned_final.csv)
- [Asynchronous test](Web_Crawler_Project/test_async.py)

## What I Did

I developed and compared crawling approaches, recorded execution and resource metrics, structured the extracted property fields, and created a cleaning pipeline for the collected data.

## Key Learning Outcomes

I learned how asynchronous I/O, concurrency limits, search partitioning, early stopping, and distributed-style data cleaning can improve a larger data-collection workflow.

## Reflection

This project showed that performance improvements require both faster execution and responsible request control. Handling network failures, empty pages, duplicate data, and Windows-specific Spark limitations also required practical problem solving.

## Possible Improvements

- Add retry logic with exponential backoff.
- Store run metrics in a comparison file instead of console output only.
- Add data validation tests and a reproducible environment file.
