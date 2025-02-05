#ifndef MQTTCONFIG_H
#define MQTTCONFIG_H

#include <Arduino.h>

struct MQTTCONFIG {
    const String mqttServer;
    const uint16_t mqttPort;
};

#endif 