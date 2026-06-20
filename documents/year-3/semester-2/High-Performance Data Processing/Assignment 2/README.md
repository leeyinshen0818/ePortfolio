# Airbnb Big Data Analysis: Performance & Memory Optimization

## Project Overview
This project demonstrates advanced techniques for managing and processing large datasets (1.8 GB+) using Python. We analyzed ~500,000 Airbnb listings to compare traditional and big-data-specific processing frameworks.

## Core Methodology
We implemented five primary strategies to handle data that approaches or exceeds memory limits:

1. **Column Selection:** Reducing width from 89 columns to 20.
2. **Chunking:** Streaming data from disk to avoid OOM (Out of Memory) errors.
3. **Data Type Optimization:** Downcasting numeric types and using categories.
4. **Sampling:** Statistically significant subsets for rapid development.
5. **Alternative Frameworks:** Leveraging **Dask** for parallelization and **Polars** for lazy execution.

## Key Results

### Memory Efficiency
- **Initial Footprint (Pandas):** 649.52 MB (100k rows)
- **Optimized Footprint:** 110.82 MB
- **Total Memory Saved:** 538.7 MB
- **Reduction Rate:** 82.94%

### Execution Speed (Full Dataset)
- **Traditional Pandas:** 26.95s
- **Dask Parallel Processing:** 33.84s
- **Polars (Fastest):** 6.09s

## Performance Comparison

| Strategy | Memory Profile | Performance | Best Use Case |
| :--- | :--- | :--- | :--- |
| **Pandas (Standard)** | High | Moderate | Small-Mid datasets |
| **Chunking** | Very Low | Slowest | extremely large files |
| **Type Optimization** | Low | N/A | Production pipelines |
| **Dask** | Distributed | Moderate | Cluster environments |
| **Polars** | Efficient | **Fastest** | High-performance local work |

## Conclusion
For high-speed processing on a single machine, **Polars** outperformed all other methods by a factor of 4x compared to Pandas. However, **Column Selection** remains the most impactful first step for any data science workflow, reducing initial load times and memory pressure by over 75%.