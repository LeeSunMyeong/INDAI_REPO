# chapter_2_data_collection.py

import requests

def collect_data(url):
    response = requests.get(url)
    if response.status_code == 200:
        return response.json()  # JSON 데이터 반환
    else:
        return None

if __name__ == "__main__":
    url = "https://api.example.com/data"  # 실제 API URL로 변경
    data = collect_data(url)
    print(data)
