#include <ArduinoJson.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
//#include <PubSubClient.h>
#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
//#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <SimpleDHT.h>
#include <MQTTClient.h>
#include "secrets.h"

// DHT11
int pinDHT11 = 16;
SimpleDHT11 dht11(pinDHT11);

int fanRelay = 7;

//WiFiClient espClient;
//PubSubClient client(espClient);

const char ssid[] = "Pakapon";
const char pwd[] = "1223334444";

// MQTT topics for the device
#define AWS_IOT_PUBLISH_TOPIC "device/DHT11/data"
#define AWS_IOT_SUBSCRIBE_TOPIC_FAN_RELAY "device/control_01/relay/fan"

WiFiClientSecure wifi_client = WiFiClientSecure();
MQTTClient mqtt_client = MQTTClient(256); // 256 indicates the maximum size for packets being published and received

StaticJsonDocument<200> json_doc;
DeserializationError json_error;

void connectAWS() {
  // Configure wifi_client with the correct certificates and keys
  wifi_client.setCACert(AWS_CERT_CA);
  wifi_client.setCertificate(AWS_CERT_CRT);
  wifi_client.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to AWS IOT Broker. 8883 is the port used for MQTT
  mqtt_client.begin(AWS_IOT_ENDPOINT, 8883, wifi_client);


  Serial.print("Connect to AWS IoT");
  // Wait for connection to AWS Iot
  mqtt_client.onMessage(incomingMessageHandler);
  while (!mqtt_client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
//  while (!mqtt_client.connected()) {
//    Serial.print(".");
//    mqtt_client.connect(THINGNAME);
//    delay(100);
//  }
  Serial.println();

  if (!mqtt_client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  Serial.println("AWS IoT Connected!");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); // 設置WiFi模式
  WiFi.begin(ssid, pwd);

  Serial.print("WiFi connecting");

  // 當WiFi連線時會回傳WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("IP 位址 : ");   // 讀取IP位址
  Serial.println(WiFi.localIP());
  Serial.println("WiFi RSSI : "); // 讀取WiFi強度
  Serial.println(WiFi.RSSI());

  pinMode(fanRelay,OUTPUT);

  connectAWS();
}

void loop() {
  // put your main code here, to run repeatedly:
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  // Start working ...
  Serial.println("========================================");
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.print(err);
    delay(1000);
    return;
  }
  
  Serial.print("Humidity = ");
  Serial.print((int) humidity);
  Serial.print("% , ");
  Serial.print("Temperature = ");
  Serial.print((int) temperature);
  Serial.print("°C ");
  Serial.println("");

  publishDHT11Info((int) humidity, (int) temperature);
  subscribeFanRelayStatus();
  mqtt_client.loop();

  delay(600000);
}

void subscribeFanRelayStatus() {
  mqtt_client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC_FAN_RELAY);
}

void publishDHT11Info(int humidity, int temperature) {
//  StaticJsonDocument<200> json_doc;
  char json_output[100];

  json_doc["humidity"] = humidity;
  json_doc["temperature"] = temperature;
  serializeJson(json_doc, json_output);
  
  mqtt_client.publish(AWS_IOT_PUBLISH_TOPIC, json_output);
  Serial.println("Sent a message");
}

void incomingMessageHandler(String &topic, String &payload) {
  Serial.println("Message received!");
  Serial.println("Topic: " + topic);
  Serial.println("Payload: " + payload);

 if (topic == AWS_IOT_SUBSCRIBE_TOPIC_FAN_RELAY){
      json_error = deserializeJson(json_doc, payload);
      if (!json_error) {
        Serial.println("Payload: " + json_doc["switch"].as<String>());
        switch_fan_relay_status(json_doc["switch"].as<String>());
      }
  }
}

void switch_fan_relay_status(String status) {
  if (status == "0") {
    digitalWrite(fanRelay,LOW);
  } else {
    digitalWrite(fanRelay,HIGH);
  }
}
