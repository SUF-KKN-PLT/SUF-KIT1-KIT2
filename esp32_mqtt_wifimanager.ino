#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>
#include "ScioSense_ENS160.h"
#include <ArduinoJson.h>
#include <ModbusMaster.h>


#include "global_variable.h"
#include "wifii_managerr.h"
#include "mqtt.h"
#include "dht22.h"
#include "lux.h"
#include "ens.h"
#include "moisture.h"
#include "npk.h"


 void setup() {
  wm.resetSettings();
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(3000);
  Serial.println("\n Starting");

  wifii_managerr_setup();
  dht_setup();
  lux_setup();
  ens_setup();
  moisture_setup();
  npk_setup();
}

void logCondition() {
  StaticJsonDocument<200> doc;
  doc["kitId"] = kit_id;
  doc["type"] = type;

  // MQTT Request Body -> Set By Condition
  doc["lux"] = g_lux;
  doc["tvoc"] = g_tvoc;
  doc["eco2"] = g_eco2;
  doc["temperature"] = g_temperature;
  doc["humidity"] = g_humidity;
  doc["output"] = "OFF"; //ON or OFF
  // End MQTT Request Body

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  if (client.connected()) {
    client.publish(topic, jsonBuffer);
    Serial.println("JSON message published:");
    Serial.println(jsonBuffer);
  } else {
    Serial.println("Not connected to MQTT broker");
  }
}

void loop() {
  if (wm_nonblocking) wm.process();
  checkButton();

  read_dht();
  read_lux();
  read_ens();
  read_moisture();
  read_npk();

  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      mqtt_setup();
    }
    client.loop();
    logCondition();
  }
}
