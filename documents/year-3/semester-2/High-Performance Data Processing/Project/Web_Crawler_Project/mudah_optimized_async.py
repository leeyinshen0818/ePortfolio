import aiohttp
import asyncio
import csv
import time
import psutil
import os

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36",
    "Accept": "application/json",
    "Referer": "https://www.mudah.my/malaysia/properties-for-sale"
}

filename = "mudah_properties_100k.csv"

# CHANGE 1: Added 'region' to the arguments
async def fetch_page(session, region, page, semaphore):
    # CHANGE 2: Added '&region={region}' to the URL
    url = f"https://www.mudah.my/_next/data/ZZIvdMD681zu5P-pSGeHT/list.json?category=2000&region={region}&type=sell&o={page}"
    
    async with semaphore:
        await asyncio.sleep(1.5)
        try:
            async with session.get(url, headers=headers) as response:
                if response.status == 200:
                    json_data = await response.json()
                    properties = json_data['pageProps']['initialStore']['ads']
                    
                    page_data = []
                    for prop in properties:
                        attr = prop.get('attributes', {})
                        
                        agent_firm = "Private Seller" 
                        agent_data_raw = attr.get('agentData')
                        
                        if agent_data_raw and isinstance(agent_data_raw, dict):
                            firm_data = agent_data_raw.get('data')
                            if firm_data and isinstance(firm_data, dict):
                                agent_firm = firm_data.get('storeParamsCompanyName', 'Private Seller')

                        row = [
                            prop.get('id', 'N/A'),
                            attr.get('subject', 'N/A'),
                            attr.get('priceAlias', 'N/A'),
                            attr.get('regionName', 'N/A'),
                            attr.get('subareaName', 'N/A'),
                            attr.get('propertyTypeName', 'N/A'),
                            attr.get('titleTypeName', 'N/A'),
                            attr.get('size', 'N/A'),
                            attr.get('roomsName', 'N/A'),
                            attr.get('bathroomName', 'N/A'),
                            agent_firm
                        ]
                        page_data.append(row)
                    
                    print(f"✅ Region {region} | Page {page} scraped successfully ({len(page_data)} items).")
                    return page_data
                else:
                    print(f"❌ Failed Region {region} | Page {page}. Status: {response.status}")
                    return None  # <--- CHANGE THIS FROM [] to None
        except Exception as e:
            print(f"⚠️ Error on Region {region} | Page {page}: {e}")
            return None  # <--- CHANGE THIS FROM [] to None

# CHANGE 3: The New Orchestrator
async def main():
    print("Starting Asynchronous Crawler with Search Space Partitioning & Early Stop...")
    start_time = time.time()
    
    semaphore = asyncio.Semaphore(5)
    
    # 1. INITIALIZE THE CSV WITH HEADERS
    # We open the file in 'w' (write) mode first to create a clean file with headers.
    with open(filename, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow([
            "Property_ID", "Title", "Price_RM", "Region", "Subarea", 
            "Property_Type", "Title_Type", "Size_sqft", "Bedrooms", 
            "Bathrooms", "Agent_Firm"
        ])

    total_records = 0
    region_ids = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

    async with aiohttp.ClientSession() as session:
        for region in region_ids:
            print(f"\n--- Starting Scrape for Region ID: {region} ---")
            region_records = 0
            
            # We scrape in BATCHES of 10 pages at a time
            for batch_start in range(1, 401, 10):
                batch_end = batch_start + 10
                
                # Create tasks just for these 10 pages
                tasks = [fetch_page(session, region, page, semaphore) for page in range(batch_start, batch_end)]
                results = await asyncio.gather(*tasks)
                
                empty_page_detected = False
                
                # 2. APPEND THE NEW DATA TO THE CSV
                # We open the file in 'a' (append) mode to add new rows without overwriting the headers.
                with open(filename, mode='a', newline='', encoding='utf-8') as file:
                    writer = csv.writer(file)
                    for page_data in results:
                        
                        # Fix 1: Ignore network errors
                        if page_data is None:
                            continue
                            
                        # Fix 2: Detect the real end of inventory
                        if len(page_data) == 0:
                            empty_page_detected = True
                            
                        # Write the actual data rows to the CSV
                        for row in page_data:
                            writer.writerow(row)
                            total_records += 1
                            region_records += 1
                
                # THE EARLY STOP: If we found an empty page in this batch, break the loop and move to the next region
                if empty_page_detected:
                    print(f"🛑 Reached the end of inventory for Region {region}. Moving to next region...")
                    break 
                
                await asyncio.sleep(2) # Brief pause between batches to stay safe

            print(f"📁 Finished Region {region}. Total records for this region: {region_records}")

    end_time = time.time()
    total_time = end_time - start_time
    
    # Calculate Throughput
    # (Note: If your baseline script doesn't have a total_records variable, 
    # just hardcode the amount you scraped, e.g., 120 for 3 pages)
    throughput = total_records / total_time 

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
    print(f"\n🚀 DONE! Scraped {total_records} total records in {round(end_time - start_time, 2)} seconds.")
if __name__ == "__main__":
    asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
    asyncio.run(main())