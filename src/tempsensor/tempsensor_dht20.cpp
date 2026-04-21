#include "tempsensor/tempsensor_dht20.hpp"

TempSensorDHT20::TempSensorDHT20(): dhtSensor(DHT20()){};

void TempSensorDHT20::initialize() {
    this->dhtSensor.begin();
}

unsigned long TempSensorDHT20::update() {
    unsigned long start_millis = millis();

    this->dhtSensor.resetSensor();
    int status = this->dhtSensor.read();

    if (status != DHT20_OK) {
        Serial.println("Failed to Read Temperature from DHT Sensor!");
        Serial.printf("Status code: %d\n", status);
    }

    return millis() - start_millis;
}

float TempSensorDHT20::getTemperature() {
    return this->dhtSensor.getTemperature();
}

float TempSensorDHT20::getHumid() {
    return this->dhtSensor.getHumidity();
}

