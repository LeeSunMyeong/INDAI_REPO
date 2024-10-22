import requests
import time

API_KEY = 'YOUR_API_KEY'

while True:
    temperature = 25
    humidity = 60
    payload = {'api_key': API_KEY, 'field1': temperature, 'field2': humidity}
    requests.post("https://api.thingspeak.com/update", params=payload)
    print("데이터 업로드:", payload)
    time.sleep(15)
