#include "tempsensor/tempsensor.hpp"

TempSensor::TempSensor(uint8_t sensorPin): 
    dhtSensor(DHT(sensorPin, DHT22)) {
}

void TempSensor::initialize() {
    this->dhtSensor.begin();
}

unsigned long TempSensor::update(bool *success) {
    unsigned long start_millis = millis();
    this->temperature = this->dhtSensor.readTemperature();
    this->humid = this->dhtSensor.readHumidity();

    if (isnan(this->temperature)) {
        *success = false;
        Serial.println("Failed to Read Temperature from DHT Sensor!");
    }
    
    if (isnan(this->humid)) {
        *success = false;
        Serial.println("Failed to Read Humidity from DHT Sensor!");
    } 

    *success = true;
    Serial.printf("Sensor Updated - Temperature: %f C Humid: %f\n", this->temperature, this->humid);

    return millis() - start_millis;
}

float TempSensor::getTemperature() {
    return this->temperature;
}

float TempSensor::getHumid() {
    return this->humid;
}

