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

To complete this project, I focused on implementing or comparing data-processing approaches and recording the available performance or output evidence. I reviewed the available files and outputs together so that the implementation, written explanation, and supporting evidence remained connected to the task objectives. Where the evidence did not clearly describe a personal contribution, I kept the description limited to the work that can be verified from this folder.

## Key Learning Outcomes

I learned how asynchronous I/O, concurrency limits, search partitioning, early stopping, and distributed-style data cleaning can improve a larger data-collection workflow.

The work also strengthened my understanding of memory-aware processing, framework comparison, concurrency, distributed processing, measurement, and optimisation. I became more aware that a technical result should be supported by a clear process, suitable evidence, and an explanation of why the selected approach was appropriate. This will help me approach related tasks more systematically in future coursework.

## Reflection

This project showed that performance improvements require both faster execution and responsible request control. Handling network failures, empty pages, duplicate data, and Windows-specific Spark limitations also required practical problem solving.

The most important challenge was making a fair performance comparison while controlling data size, environment, and implementation differences. Working through this required me to check the task in smaller stages and compare the result with the available requirements or evidence. This process improved my patience and made me more careful about verifying technical work before presenting it.

Overall, this project contributed to my development by combining practical work with documentation and reflection. It showed me which parts I can now complete with more confidence and which areas still require further practice. The experience will be useful when I work on larger projects that demand clearer organisation, stronger testing, and more independent technical decisions.

## Possible Improvements

A useful next step would be to add retry logic with exponential backoff. Store run metrics in a comparison file instead of console output only. A useful next step would be to add data validation tests and a reproducible environment file.

In a future version, I would also focus on repeatable benchmarks, clearer environment specifications, additional data sizes, error handling, and discussion of scalability limits. These additions would make the work easier to understand, reproduce, and evaluate while providing stronger evidence of the development process.
