#include <display/display.hpp>
#include <Arduino.h>

/**
 * @brief Logs a message to Serial and to a given display and appends a line. 
 * 
 * @param disp Reference to a Display object which should be used for logging
 * @param message Message which should be logged
 */
void logln(SSD1306Wire* disp, const char *message);
