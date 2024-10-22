import json
import time
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient

client = AWSIoTMQTTClient("myClientID")
client.configureEndpoint("your-endpoint.amazonaws.com", 8883)
client.configureCredentials("root-CA.crt", "private.pem.key", "certificate.pem.crt")

client.connect()

while True:
    message = {
        'temperature': 25,
        'humidity': 60
    }
    client.publish("sensor/data", json.dumps(message), 1)
    print("메시지 발행:", message)
    time.sleep(2)
