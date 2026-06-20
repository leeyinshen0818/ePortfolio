import requests
import json
import csv
import time
import psutil  # [NEW] For tracking CPU/Memory
import os      # [NEW] For getting the current process ID

# 1. Setup your Disguise
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36",
    "Accept": "application/json"
}

filename = "mudah_properties_structured.csv"

# [NEW] Start the performance clock and record counter
start_time = time.time()
total_records = 0

# 2. Open the file and write out the CLEAN headers
with open(filename, mode='w', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow([
        "Property_ID", "Title", "Price_RM", "Region", "Subarea", 
        "Property_Type", "Title_Type", "Size_sqft", "Bedrooms", 
        "Bathrooms", "Agent_Firm"
    ])

    print("Starting structured baseline crawler...")

    # Loop through the first 10 pages for the controlled experiment
    for page in range(1, 11): 
        print(f"Fetching Page {page}...")
        url = f"https://www.mudah.my/_next/data/ZZIvdMD681zu5P-pSGeHT/list.json?category=2000&type=sell&o={page}"

        try:
            response = requests.get(url, headers=headers)
            
            if response.status_code == 200:
                json_data = response.json()
                properties = json_data['pageProps']['initialStore']['ads']
                
                # [NEW] Add to our running total of records scraped
                total_records += len(properties)
                
                # 3. Extract the specific fields for each property
                for prop in properties:
                    attr = prop.get('attributes', {})
                    
                    # Core Identifiers
                    prop_id = prop.get('id', 'N/A')
                    title = attr.get('subject', 'N/A')
                    price = attr.get('priceAlias', 'N/A')
                    
                    # Location
                    region = attr.get('regionName', 'N/A')
                    subarea = attr.get('subareaName', 'N/A')
                    
                    # Specifications
                    prop_type = attr.get('propertyTypeName', 'N/A')
                    title_type = attr.get('titleTypeName', 'N/A')
                    size = attr.get('size', 'N/A')
                    beds = attr.get('roomsName', 'N/A')
                    baths = attr.get('bathroomName', 'N/A')
                    
                    # Agent Firm (requires navigating deeper into the JSON)
                    agent_firm = "N/A"
                    agent_data = attr.get('agentData', {}).get('data', {})
                    if agent_data:
                        agent_firm = agent_data.get('storeParamsCompanyName', 'N/A')

                    # Write the extracted, clean row to the CSV
                    writer.writerow([
                        prop_id, title, price, region, subarea, 
                        prop_type, title_type, size, beds, baths, agent_firm
                    ])
                
                print(f"Successfully saved {len(properties)} structured records from Page {page}.")
            else:
                print(f"Failed to load page {page}. Status Code: {response.status_code}")

            time.sleep(2) 

        except Exception as e:
            print(f"An error occurred on page {page}: {e}")

print("\nTest crawl complete. Check the structured CSV file!")

# ---------------------------------------------------------
# [NEW] --- PERFORMANCE METRICS TRACKING ---
# ---------------------------------------------------------
end_time = time.time()
total_time = end_time - start_time

# Calculate Throughput (Prevent division by zero)
throughput = total_records / total_time if total_time > 0 else 0

# Capture Hardware Usage for this specific Python process
process = psutil.Process(os.getpid())
memory_used_mb = process.memory_info().rss / (1024 * 1024)  # Convert bytes to Megabytes
cpu_usage = psutil.cpu_percent(interval=1.0) # Measures CPU usage over 1 second

print("\n" + "="*40)
print("📊 FINAL PERFORMANCE METRICS")
print("="*40)
print(f"⏱️ Total Processing Time: {round(total_time, 2)} seconds")
print(f"🚀 Throughput:            {round(throughput, 2)} records / second")
print(f"💾 Peak Memory (RAM) Use: {round(memory_used_mb, 2)} MB")
print(f"🧠 CPU Usage:             {cpu_usage} %")
print("="*40)