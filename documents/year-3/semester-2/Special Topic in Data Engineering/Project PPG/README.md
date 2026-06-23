# PPG Inventory Risk Analytics Project

## Overview

This group project proposes an Azure-based data architecture for analysing inventory and supply risks in a PPG-style manufacturing environment. The available evidence covers data ingestion, layered storage, data processing, governance, stockout-risk analysis, sales-order impact analysis, and reporting.

The architecture moves CSV source data through Azure Data Factory into Azure Data Lake Storage Gen2. The data is organised into bronze, silver, and gold layers before being processed through Azure Synapse Serverless SQL and prepared for Power BI reporting.

## Objectives

- Design a cloud data architecture for inventory-risk analytics.
- Integrate material, inventory, purchasing, production, supplier, and sales-order data.
- Clean and standardise source records using layered data processing.
- Identify materials below their reorder levels.
- Estimate stock-cover days and possible stockout risks.
- Examine how material shortages could affect customer sales orders.
- Prepare analytics-ready outputs for dashboards and risk reporting.
- Include data-quality, access-control, lineage, and validation considerations.

## Tools and Technologies

- Microsoft Azure
- Azure Data Factory
- Azure Data Lake Storage Gen2
- Azure Synapse Serverless SQL
- Power BI
- CSV datasets
- Bronze, silver, and gold data layers
- Role-Based Access Control (RBAC)
- Data-quality and validation rules

## Folder Contents / Evidence

| Evidence | Description |
| --- | --- |
| [Final project report](G8_PPGProject_Final.pdf) | Complete written group-project documentation |
| [Presentation slides](G8_PPGProject_Slide.pdf) | Summary of the project approach and findings |
| [Data architecture diagram](<Data architecture.png>) | Azure architecture from source ingestion to reporting |
| [Azure output folder](<Chap 5 Azure>) | Query outputs and inventory-risk analysis evidence |
| [Customer-impact summary](<Chap 5 Azure/Summary.csv>) | Customers and orders affected by at-risk materials |
| [Materials below reorder level](<Chap 5 Azure/Test Q1_New.csv>) | Inventory records identified below their reorder thresholds |
| [Stockout-risk output](<Chap 5 Azure/Test Q6_New.csv>) | Stock cover, lead time, and stockout-risk calculations |
| [Sales-order impact output](<Chap 5 Azure/Test Q7.csv>) | Orders potentially affected by material shortages |

## What I Did

I contributed to the group project by working with the available project evidence and helping connect the business problem with a structured Azure data-engineering solution. The work involved examining inventory-related datasets, understanding the required data flow, and documenting how source records could move through ingestion, storage, transformation, governance, and reporting stages.

I also worked with the analysis outputs used to identify materials below reorder levels, calculate stock-cover risk, and connect at-risk materials with customer sales orders. The architecture and supporting documentation were organised so that the technical workflow remained connected to the inventory-risk questions addressed by the project. The exact division of responsibilities among group members can be added later if required.

## Key Learning Outcomes

This project strengthened my understanding of how a cloud data platform can support supply-chain and inventory analysis. I learned how Azure Data Factory, Data Lake Storage, Synapse SQL, and Power BI can be connected as different stages of a data pipeline rather than treated as separate tools.

I also learned that inventory-risk reporting depends on more than current stock quantity. Reorder levels, average daily consumption, supplier lead time, production requirements, and customer delivery dates all affect whether a material may cause operational disruption. The project also increased my awareness of data governance, validation, lineage, and access control within an analytical architecture.

## Reflection

This project was valuable because it applied data-engineering concepts to a practical manufacturing and inventory problem. Instead of analysing one isolated dataset, the proposed solution connected materials, inventory snapshots, purchase orders, production orders, suppliers, and sales orders. This helped me understand why data integration is important when business risks depend on relationships between several operational processes.

The main challenge was designing a workflow that remained understandable while covering ingestion, storage layers, transformations, analytics, governance, and reporting. Inventory-risk calculations also needed to be interpreted carefully because a low stock quantity alone does not explain the full risk. Comparing stock cover with lead time and linking shortages to sales orders provided a more meaningful view of possible business impact.

Overall, the project improved my ability to connect technical architecture with business requirements. It showed me that a useful data solution should provide traceable and validated information that decision-makers can act on. The experience strengthened my understanding of Azure data services, layered architecture, inventory analytics, and the importance of explaining technical results clearly through reports, diagrams, and presentation evidence.

## Possible Improvements

The project could be improved by adding the original source datasets, reproducible pipeline or SQL scripts, detailed schema definitions, and screenshots of the Azure resources and Power BI dashboard. A data dictionary would also make the relationships between materials, orders, suppliers, and inventory fields easier to understand.

A future version could include automated scheduling, monitoring, alert notifications, incremental data loading, and a documented recovery process for failed pipeline activities. Additional security and governance evidence could demonstrate how RBAC, validation rules, quarantine handling, and data lineage would operate in the implemented environment.

[← Back to Special Topic in Data Engineering](../README.md)
