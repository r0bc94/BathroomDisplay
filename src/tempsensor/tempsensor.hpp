#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <Arduino.h>
#include <DHT.h>

class TempSensor {
    public:
        TempSensor(uint8_t sensorPin); 

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
         * @brief Reads and returns the current Temperature read by the Sensor or an
         * empty string, if the reading failed.
         * 
         * @return const String Temperature or empty, if reading failed
         */
        const String getTemperature();

        /**
         * @brief Reads and returns the current Humidity read by the Sensor or an
         * empty string, if the reading failed.
         * 
         * @return const String Humidity or empty, if reading failed
         */
        const String getHumid();

    private:
        DHT dhtSensor;
        float temperature;
        float humid;
};



#endif