# Mudah Property Web Crawler

## Overview

This folder contains the implementation and datasets for the High-Performance Data Processing property-crawler project.

## Implementation

- `mudah_baseline.py` performs a controlled sequential crawl and records timing, throughput, memory, and CPU measurements.
- `mudah_optimized_async.py` uses `aiohttp`, `asyncio`, a semaphore, regional partitioning, batching, and early stopping.
- `clean_data.py` uses PySpark to remove duplicate or incomplete records and standardise agent information.

## Evidence

- [Baseline crawler](mudah_baseline.py)
- [Optimised crawler](mudah_optimized_async.py)
- [Cleaning pipeline](clean_data.py)
- [Raw property data](mudah_properties_100k.csv)
- [Cleaned output](mudah_100k_cleaned_final.csv)
- [Async test](test_async.py)

## Run Notes

Install the required Python packages before running the scripts. Network endpoints and page structures may change, so the crawler may require maintenance in the future.

See the [parent project README](../README.md) for objectives, learning outcomes, reflection, and possible improvements.
