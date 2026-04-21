#ifndef TEMPSENSOR_DHT22_H
#define TEMPSENSOR_DHT22_H

#include <Arduino.h>
#include <DHT.h>

#include "tempsensor/tempsensor.hpp"

class TempSensorDHT22 : public TempSensor {
    public:
        TempSensorDHT22();
        TempSensorDHT22(uint8_t sensorPin); 

        /**
         * @brief Initializes the DHT Sensor.
         * 
         */
        void initialize();

        /**
         * @brief Triggers a reading and updating the internal values.
         * 
         * @returns The number of millis the operation took. 
         */
        unsigned long update();

        /**
         * @brief Returns the last measured temperature value of the sensor. Call update() to
         * update the value.
         * 
         * @return float last measured temperature or TEMP_READING_FAILED if the last update failed.
         */
        float getTemperature();

        /**
         * @brief Returns the last measured humidity value of the sensor. Call update() to
         * update the value.
         * 
         * @return float last measured humidity or HUMID_READING_FAILED if the last update failed.
         */
        float getHumid();

    private:
        DHT dhtSensor;
        float temperature;
        float humid;
};

#endif