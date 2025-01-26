#include "logger/logger.hpp"

void logln(SSD1306Wire* disp, const char *message) {
    Serial.println(message);

    if(disp != nullptr) {
        disp->println(message);
    }
}

