import paho.mqtt.client as mqtt
import time

broker_address = "localhost"  # 브로커 주소
client = mqtt.Client("Publisher")  # 클라이언트 이름
client.connect(broker_address)  # 브로커 연결

while True:
    message = "Hello MQTT"
    client.publish("test/topic", message)
    print("메시지 발행:", message)
    time.sleep(2)
