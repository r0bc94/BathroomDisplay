#include "clock/clock.hpp"

Clock::Clock(const char *ntpAddress, long offset, unsigned long updateInterval) :
        udpClient(), 
        ntpClient(udpClient, ntpAddress, offset, updateInterval) {}

const String Clock::getFormattedTime() {
    return this->ntpClient.getFormattedTime();
}

const String Clock::getFormattedDate() {
    time_t epoch = this->ntpClient.getEpochTime();
    struct tm *timeInfo = localtime(&epoch);
    char datebuff[20];

    //Write the Time Format to the Date buffer
    sprintf(datebuff, "%02d.%02d.%04d", timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year);
    return String(datebuff);
}

bool Clock::update() {
    return this->ntpClient.update();
}
