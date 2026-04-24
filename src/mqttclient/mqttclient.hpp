#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include<PubSubClient.h>
#include<ESP8266WiFi.h>
#include<SSD1306.h>

#include "logger/logger.hpp"
#include "tempsensor/tempsensor.hpp"

typedef int8_t MQTT_CONNECT_STATE;

class MqttClient {
    public:
        /**
         * @brief Creates a new MqttClient object with a given 
         * Wifi Client.
         * 
         * @param WiFiClient Wifi Client which should be used for MQTT Connections.
         * @param tempsensor Reference to an already initialized tempsensor object.
         * @param root_topic The root topic which will be used to publish MQTT messages. This must NOT end with a /. 
         * 
         */
        MqttClient(WiFiClient &wifiClient, TempSensor &tempsensor, String root_topic);

        /**
         * @brief Initialize and connect the MQTT - Client.
         * 
         * @param mqttServer Server which should be used for MQTT
         * @param mqttPort Port where the MQTT Server listens
         */
        MQTT_CONNECT_STATE initialize(const char *mqttServer, const uint16_t mqttPort, SSD1306Wire *disp);

        /**
         * @brief Try to reestablish a connection with the registered MQTT - Client.
         * 
         * @return MQTT_CONNECT_STATE Sucess or error code according to PubSubClient Definitons
         */
        MQTT_CONNECT_STATE reconnect(SSD1306Wire *disp);

        /**
         * @brief Publishes the current Temperature and humidity measurements. 
         * 
         * @return uint8_t The number of Millis the operation took. 
         */
        unsigned long publishTempHumidMeasurements();


        /**
         * @brief Publishes a heratbeat message to the MQTT - Server on the specfied topic to
         * indicate, that the node is still alive.
         * 
         * @return unsigned long The number of Millis the operation took. 
         */
        unsigned long publishHeartbeat();

    private:
        PubSubClient mqttClient;
        TempSensor &tempsensor;

        boolean publishMessage(const String &topic, const String &message);
        String root_topic;
};



#endif