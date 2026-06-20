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

async def fetch_page(session, region, page, semaphore):
    url = f"https://www.mudah.my/_next/data/ZZIvdMD681zu5P-pSGeHT/list.json?category=2000&region={region}&type=sell&o={page}"
    async with semaphore:
        await asyncio.sleep(1.5)
        try:
            async with session.get(url, headers=headers) as response:
                if response.status == 200:
                    json_data = await response.json()
                    return json_data['pageProps']['initialStore']['ads']
                return []
        except:
            return []

async def main():
    print("Starting Optimized Async TEST (10 Pages)...")
    start_time = time.time()
    semaphore = asyncio.Semaphore(5)
    total_records = 0
    
    async with aiohttp.ClientSession() as session:
        # Testing with EXACTLY 10 pages from Region 12
        tasks = [fetch_page(session, 12, page, semaphore) for page in range(1, 11)]
        results = await asyncio.gather(*tasks)
        
        for page_data in results:
            if page_data:
                total_records += len(page_data)

    # --- PERFORMANCE METRICS TRACKING ---
    end_time = time.time()
    total_time = end_time - start_time
    throughput = total_records / total_time if total_time > 0 else 0
    process = psutil.Process(os.getpid())
    memory_used_mb = process.memory_info().rss / (1024 * 1024)
    cpu_usage = psutil.cpu_percent(interval=1.0)

    print("\n" + "="*40)
    print("⚡ ASYNC OPTIMIZED METRICS")
    print("="*40)
    print(f"⏱️ Total Processing Time: {round(total_time, 2)} seconds")
    print(f"🚀 Throughput:            {round(throughput, 2)} records / second")
    print(f"💾 Peak Memory (RAM):     {round(memory_used_mb, 2)} MB")
    print(f"🧠 CPU Usage:             {cpu_usage} %")
    print("="*40)

if __name__ == "__main__":
    asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
    asyncio.run(main())