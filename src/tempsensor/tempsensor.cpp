#include "tempsensor/tempsensor.hpp"

TempSensor::TempSensor(uint8_t sensorPin): 
    dhtSensor(DHT(sensorPin, DHT22)) {
}

void TempSensor::initialize() {
    this->dhtSensor.begin();
}

unsigned long TempSensor::update() {
    unsigned long start_millis = millis();
    this->temperature = this->dhtSensor.readTemperature();
    this->humid = this->dhtSensor.readHumidity();

    Serial.printf("Sensor Updated - Temperature: %f C Humid: %f\n", this->temperature, this->humid);

    return millis() - start_millis;
}

const String TempSensor::getTemperature() {
    char formatBuffer[7];

    if (isnan(this->temperature)) {
        Serial.println("Failed to Read Temperature from DHT Sensor!");
        return "";
    }

    sprintf(formatBuffer, "%.1f\xB0 C", this->temperature);
    return String(formatBuffer);    
}

const String TempSensor::getHumid() {
    char formatBuffer[7];

    if (isnan(this->humid)) {
        Serial.println("Failed to Read Humidity from DHT Sensor!");
        return "";
    }

    sprintf(formatBuffer, "%.1f\x25", this->humid);
    return String(formatBuffer);    
}

