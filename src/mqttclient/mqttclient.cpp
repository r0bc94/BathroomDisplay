#include "mqttclient/mqttclient.hpp"

MqttClient::MqttClient(WiFiClient &wifiClient, TempSensor &tempsensor): 
    mqttClient(PubSubClient(wifiClient)),
    tempsensor(tempsensor) {
}

MQTT_CONNECT_STATE MqttClient::reconnect(SSD1306Wire *disp) {
    char logbuffer[512];
    MQTT_CONNECT_STATE connect_state = 0;
    for (int i = 0; !this->mqttClient.connected() && i < 10; i++) {
        logln(disp, "Connecting MQTT...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        // Attempt to connect
        Serial.printf("Attempt %d\n", i);
        if (this->mqttClient.connect(clientId.c_str())) {
            return MQTT_CONNECTED;
        } else {
            connect_state = this->mqttClient.state();
            sprintf(logbuffer, "MQTT Con Failed: %d", connect_state);
            logln(disp, logbuffer);
            Serial.println(connect_state);
            delay(1000);
        }
  }

  return connect_state;
}

MQTT_CONNECT_STATE MqttClient::initialize(const char *mqttServer, const uint16_t mqttPort, SSD1306Wire *disp) {
    this->mqttClient.setServer(mqttServer, mqttPort);
    return this->reconnect(disp);
}

boolean MqttClient::publishMessage(const String &topic, const String &message) {
    Serial.printf("Publishing Message: %s to topic: %s", message.c_str(), topic.c_str());

    // Reconnect before publishing
    if (!this->mqttClient.connected()) {
        int8_t connect_state = this->reconnect(nullptr);
        if (connect_state != MQTT_CONNECTED) {
            Serial.printf("Failed to reestablish MQTT - Connection: %d\n", connect_state);
            return false;
        }
    }

    boolean publish_success = this->mqttClient.publish(topic.c_str(), message.c_str());
    Serial.printf("MQTT Publish Temperature State: %d\n", publish_success);
    return publish_success;
}

unsigned long MqttClient::publishTempHumidMeasurements(const String &topic) {
    unsigned long startmillis = millis();
    String temperature = this->tempsensor.getTemperature();
    String humid = this->tempsensor.getHumid();

    this->publishMessage(topic + "/temperature", temperature);
    this->publishMessage(topic + "/humid", humid);

    return millis() - startmillis;
}