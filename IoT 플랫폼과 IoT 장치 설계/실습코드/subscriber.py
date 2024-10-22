import paho.mqtt.client as mqtt

broker_address = "localhost"  # 브로커 주소

def on_message(client, userdata, message):
    print("메시지 수신:", str(message.payload.decode("utf-8")))

client = mqtt.Client("Subscriber")
client.on_message = on_message
client.connect(broker_address)
client.subscribe("test/topic")
client.loop_forever()
