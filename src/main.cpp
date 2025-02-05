#include <Arduino.h>

#include <Wire.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "SSD1306Wire.h"

#include "SETTINGS.hpp"
#include "logger/logger.hpp"
#include "tempsensor/tempsensor.hpp"
#include "mqttclient/mqttclient.hpp"

char logbuffer[512];

Clock clk(NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
TempSensor tmpsensor(D4);
WiFiClient wificlient;
MqttClient mqttClient(wificlient, tmpsensor);

DISPLAYCONFIG dconfig = {128, 64, D2, D1};
DISPLAY_OBJECTS dobj = {clk, tmpsensor};

Display display(&dconfig, &dobj);

unsigned int startmil = 0;

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
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  sprintf(logbuffer, "Connected!\nIP: %s\n", WiFi.localIP().toString().c_str());
  logln(rawDisplay, logbuffer);
  Serial.println(WiFi.localIP());

  // Initializing NTP
  logln(rawDisplay, "Initializing NTP..");
  clk.update();

  // Initializing DHT Sensor
  logln(rawDisplay, "Initializing Temp Sensor");
  tmpsensor.initialize();
  delay(5000);
  tmpsensor.update();

  // Connecting MQTT
  mqttClient.initialize(MQTT_SERVER, MQTT_PORT, rawDisplay);
  logln(rawDisplay, "MQTT Initialized");
  startmil = millis();
}

void loop() {
  unsigned int updatetime = display.update();

  if (millis() - startmil >= 5000) {
    logln(nullptr, "Updating Temperature Sensor");
    updatetime += tmpsensor.update();
    startmil = millis();
  }


  
  delay(1000 - updatetime);
}

