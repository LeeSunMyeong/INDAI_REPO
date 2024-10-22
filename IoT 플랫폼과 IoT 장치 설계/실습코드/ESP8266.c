#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 2     // D4 핀
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "YOUR_MQTT_BROKER_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  dht.begin();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  Serial.println("WiFi 연결 중...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi 연결 완료");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    String payload = String("{\"temperature\":") + t + ",\"humidity\":" + h + "}";
    client.publish("sensor/data", payload.c_str());
    Serial.println("데이터 발행: " + payload);
  } else {
    Serial.println("센서에서 데이터를 읽을 수 없습니다.");
  }
  delay(2000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("MQTT 연결 중...");
    if (client.connect("ESP8266Client")) {
      Serial.println("MQTT 연결 성공");
    } else {
      Serial.print("MQTT 연결 실패, rc=");
      Serial.print(client.state());
      Serial.println(" 5초 후 재시도");
      delay(5000);
    }
  }
}
