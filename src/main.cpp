#include <Arduino.h>

#include <Wire.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <cstdint>
#include "PubSubClient.h"
#include "SSD1306Wire.h"

#include "SETTINGS.hpp"
#include "logger/logger.hpp"
#include "tempsensor/tempsensor.hpp"
#include "mqttclient/mqttclient.hpp"

char logbuffer[512];

Clock clk(NTP_ADDRESS, NTP_OFFSET, NTP_POSIX_TIMEZONESTRING, NTP_INTERVAL);

TempSensor tmpsensor(D3);
bool tempSensorReadSuccess = false;

WiFiClient wificlient;
MqttClient mqttClient(wificlient, tmpsensor, MQTT_ROOT_TOPIC);

DISPLAYCONFIG dconfig = {128, 64, D2, D1};
DISPLAY_OBJECTS dobj = {clk, tmpsensor};

Display display(&dconfig, &dobj);

MQTT_CONNECT_STATE mqttstate = 0;

unsigned long update_millis = 0;
unsigned long publish_millis = 0;

void setup() {
  Serial.begin(74880);
  display.initialize();
  SSD1306Wire *rawDisplay = &display.getDisplay();
  rawDisplay->setBrightness(128); 

  display.displayWelcomeFrame();
  delay(3000);

  // Initializing Wifi
  logln(rawDisplay, "Connecting Wifi...");
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  
  uint8_t retry = 0;
  for (; WiFi.status() != WL_CONNECTED && retry < WIFI_RETRY_COUNT; retry++) {
    delay(500);
    Serial.print(".");
  }

  if (retry == WIFI_RETRY_COUNT) {
    logln(rawDisplay, "Wifi Connection Failed!");
    delay(2000);
  }

  sprintf(logbuffer, "Connected!\nIP: %s\n", WiFi.localIP().toString().c_str());
  logln(rawDisplay, logbuffer);

  // Initializing NTP
  logln(rawDisplay, "Initializing NTP..");
  clk.update();

  // Initializing DHT Sensor
  logln(rawDisplay, "Initializing Temp Sensor");
  tmpsensor.initialize();
  delay(5000);
  tmpsensor.update(&tempSensorReadSuccess);
  (tempSensorReadSuccess) ?
    logln(rawDisplay, "OK") 
    : logln(rawDisplay, "FAILED");
  

  delay(2000);

  // Connecting MQTT
  mqttstate = mqttClient.initialize(MQTT_SERVER, MQTT_PORT, rawDisplay);
  logln(rawDisplay, "MQTT Initialized");
  
  delay(2000);

  update_millis = millis();
  publish_millis = millis();
}

char logbuff[128];
void loop() {
  unsigned int updatetime = display.update();
  long sleeptime = updatetime;

  if (millis() - update_millis >= UPDATE_INTERVAL) {
    logln(nullptr, "Updating Temperature Sensor");
    sleeptime -= tmpsensor.update(&tempSensorReadSuccess);

    if (!tempSensorReadSuccess) {
      logln(nullptr, "Failed to read from the temp sensor!");
    }

    if (mqttstate == MQTT_CONNECTED) {
      logln(nullptr, "Publishing heartbeat message");
      sleeptime -= mqttClient.publishHeartbeat();
    } else {
      logln(nullptr, "MQTT Connection Failed");
    }

    logln(nullptr, "Updating Clock");
    clk.update();

    update_millis = millis();
  }

  if (millis() - publish_millis >= MQTT_PUBLISH_INTERVAL && mqttstate == MQTT_CONNECTED) {
    sprintf(logbuff, "Publishing Results to MQTT Server: %s\n", MQTT_SERVER);
    logln(nullptr, logbuff);
    sleeptime -= mqttClient.publishTempHumidMeasurements();
    
    publish_millis = millis();
  }
  
  if (sleeptime <= 0) {
    Serial.printf("Cant keep up. Lower Framerate!\n");
  } else {
    //Serial.printf("Sleeping for %ld milliseconds\n", sleeptime);
    delay(sleeptime);
  }
}

