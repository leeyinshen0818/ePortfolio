from pyspark.sql import SparkSession
from pyspark.sql.functions import col, when

# 1. Initialize the Spark Session (This creates the distributed compute cluster on your machine)
spark = SparkSession.builder \
    .appName("MudahDataCleaning") \
    .config("spark.executor.memory", "4g") \
    .getOrCreate()

print("PySpark Session Initialized.")

# 2. Load the Raw Data
# We tell Spark it has a header and to infer the data types
raw_df = spark.read.csv("mudah_properties_100k.csv", header=True, inferSchema=True)
initial_count = raw_df.count()
print(f"Loaded {initial_count} raw records.")

# 3. Data Cleaning Pipeline
# A. Drop Duplicates: Dealers often post the same property multiple times. We keep only unique Property_IDs.
cleaned_df = raw_df.dropDuplicates(["Property_ID"])

# B. Handle Missing Values: Drop rows where critical fields (Price or Size) are completely missing/Null
cleaned_df = cleaned_df.dropna(subset=["Price_RM", "Size_sqft"])

# C. Standardize the Agent Firm column (Clean up "Private Seller" vs actual firms)
cleaned_df = cleaned_df.withColumn("Agent_Firm", 
                                   when(col("Agent_Firm") == "N/A", "Private Seller")
                                   .otherwise(col("Agent_Firm")))

final_count = cleaned_df.count()
print(f"Cleaning complete. Filtered down to {final_count} pristine records.")
print(f"Dropped {initial_count - final_count} invalid or duplicate rows.")

# 4. Save the "Silver Layer" Data (USING THE PANDAS BRIDGE)
print("Converting to Pandas to bypass Windows Hadoop write limitations...")
# Convert the distributed Spark dataframe to a local Pandas dataframe
pandas_df = cleaned_df.toPandas()

# Save using Pandas
pandas_df.to_csv("mudah_100k_cleaned_final.csv", index=False, encoding='utf-8')

print("✅ Clean dataset successfully saved as: mudah_100k_cleaned_final.csv")
spark.stop()