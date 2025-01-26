#include <Arduino.h>

#include <Wire.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "SSD1306Wire.h"

#include "SETTINGS.hpp"
// #include "display/display.hpp"
#include "logger/logger.hpp"

DISPLAYCONFIG dconfig = {128, 64, D2, D1};

Display display(&dconfig);

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
char logbuffer[512];

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
  timeClient.update();
  display.setNTPClient(&timeClient);
}

void loop() {
  unsigned int updatetime = display.update();
  delay(1000 - updatetime);
}

