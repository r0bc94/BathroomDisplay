#include "tempsensor/tempsensor_dht22.hpp"

TempSensorDHT22::TempSensorDHT22(uint8_t sensorPin): 
    dhtSensor(DHT(sensorPin, DHT22)) {
}

void TempSensorDHT22::initialize() {
    this->dhtSensor.begin();
}

unsigned long TempSensorDHT22::update() {
    unsigned long start_millis = millis();
    this->temperature = this->dhtSensor.readTemperature();
    this->humid = this->dhtSensor.readHumidity();

    if (isnan(this->temperature)) {
        Serial.println("Failed to Read Temperature from DHT Sensor!");
    }
    
    if (isnan(this->humid)) {
        Serial.println("Failed to Read Humidity from DHT Sensor!");
    } 

    Serial.printf("Sensor Updated - Temperature: %f C Humid: %f\n", this->temperature, this->humid);

    return millis() - start_millis;
}

float TempSensorDHT22::getTemperature() {
    return this->temperature;
}

float TempSensorDHT22::getHumid() {
    return this->humid;
}

