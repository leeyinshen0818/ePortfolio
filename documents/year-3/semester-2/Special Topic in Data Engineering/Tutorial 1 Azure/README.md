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

To complete this tutorial, I focused on completing the available tutorial or assignment workflow and organising its technical and written evidence. I reviewed the available files and outputs together so that the implementation, written explanation, and supporting evidence remained connected to the task objectives. Where the evidence did not clearly describe a personal contribution, I kept the description limited to the work that can be verified from this folder.

## Key Learning Outcomes

I learned how storage, transformation, table formats, and reporting tools connect within a basic data pipeline.

The work also strengthened my understanding of cloud data engineering, distributed processing, artificial intelligence, analytical pipelines, academic writing, and technical communication. I became more aware that a technical result should be supported by a clear process, suitable evidence, and an explanation of why the selected approach was appropriate. This will help me approach related tasks more systematically in future coursework.

## Reflection

This tutorial was useful because it moved beyond local data analysis into a cloud workflow. The main challenge was managing paths, formats, and access configuration correctly.

The most important challenge was connecting several tools and processing stages while keeping paths, formats, configurations, and explanations consistent. Working through this required me to check the task in smaller stages and compare the result with the available requirements or evidence. This process improved my patience and made me more careful about verifying technical work before presenting it.

Overall, this tutorial contributed to my development by combining practical work with documentation and reflection. It showed me which parts I can now complete with more confidence and which areas still require further practice. The experience will be useful when I work on larger projects that demand clearer organisation, stronger testing, and more independent technical decisions.

## Possible Improvements

A useful next step would be to replace embedded credentials with Azure secrets or managed identities. A useful next step would be to add a pipeline diagram and reproducible setup instructions.

In a future version, I would also focus on reproducible setup instructions, architecture diagrams, stronger security practices, validation evidence, and clearer comparison of alternative approaches. These additions would make the work easier to understand, reproduce, and evaluate while providing stronger evidence of the development process.
