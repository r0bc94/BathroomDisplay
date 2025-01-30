#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <WiFiUdp.h>
#include <NTPClient.h>

class Clock {
    public:
        Clock(const char *ntpAddress, long offset, unsigned long updateInterval);

        /**
         * @brief Returns a String which contains the formatted time. 
         * 
         * The time format looks like: 
         * HH:MM:SS
         * 
         * @return const String A string containing the current time in a well known format
         */
        const String getFormattedTime();

        /**
         * @brief REturns a String which contains the formatted date.
         * 
         * @return const String Current Date as a formatted String. 
         */
        const String getFormattedDate();

        /**
         * @brief Wrapper around the update() Method from the ntpclient. 
         * 
         * @return true if the clock was updated successfully
         * @return false if the clock update failed
         */
        bool update(); 

    private:
        WiFiUDP udpClient;
        NTPClient ntpClient;
};

#endif 