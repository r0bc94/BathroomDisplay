#ifndef TEMPSENSOR_DHT20_H
#define TEMPSENSOR_DHT20_H

#include "tempsensor.hpp"
#include "DHT20.h"

class TempSensorDHT20 : public TempSensor {
    public:
        /**
         * @brief Construct a new Temp Sensor DHT22 sensor object.
         * 
         */
        TempSensorDHT20();

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
        DHT20 dhtSensor;
        float temperature;
        float humid;
};


#endif
