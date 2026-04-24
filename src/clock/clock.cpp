#include "clock/clock.hpp"

Clock::Clock(const char *ntpAddress, long offset, const char *tzstring, unsigned long updateInterval) :
        udpClient(), 
        ntpClient(udpClient, ntpAddress, offset, updateInterval) {
            configTzTime(tzstring, nullptr);
        }

const String Clock::getFormattedTime() {
    time_t epoch = this->ntpClient.getEpochTime();
    struct tm *timeInfo = localtime(&epoch);
    int hours = timeInfo->tm_hour;
    int minutes = timeInfo->tm_min;
    int seconds = timeInfo->tm_sec;

    String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);
    String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);
    String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

    return hoursStr + ":" + minuteStr + ":" + secondStr;
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
