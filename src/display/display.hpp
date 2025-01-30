/**
 * @file display.hpp
 * @author Robin
 * @brief Display Class which abstracts away all display related functions
 * @version 0.1
 * @date 2025-01-05
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdbool.h>

#include <Wire.h>
#include <time.h>
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"

#include <NTPClient.h>

#include "types/temphumid.hpp"
#include "types/displayconfig.hpp"
#include "types/displayobjects.hpp"

#define NUMBER_OF_FRAMES 1

const uint8_t activeSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000
};

const uint8_t inactiveSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000
};

void digitalClockFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);

class Display {
    public:
        /**
         * @brief Construct a new Display object
         * 
         * @param config Pointer which points to the displayconfig object.
         */
        Display(DISPLAYCONFIG *config, DISPLAY_OBJECTS *dispobjects);

        /**
         * @brief Initializes the display connected to the given pins.
         * 
         * @return true if the display was initialized successfully
         * @return false if there was an error during the display initialization
         */
        bool initialize();

        /**
         * @brief Sets the current Temperature and Humidity of the display.
         * 
         * @param temphumid Struct which contains the temperature and humidity information
         */
        void setTemperatureHumid(TempHumid* temphumid);

        /**
         * @brief Updates the display and returns the remaining ticks
         * 
         * @return unsigned int Number of the remaining ticks
         */
        unsigned int update();

        /**
         * @brief Returns a pointer to the raw Display object.
         * 
         * @return SSD1306Wire Raw Display object which can be used to directly manipulate the
         * display. 
         */
        SSD1306Wire& getDisplay();
        /**
         * @brief Writes a welcome image to the display.
         * 
         */
        void displayWelcomeFrame();

    private:
        DISPLAYCONFIG *displayconfig;
        DISPLAY_OBJECTS *dispobjects;
        SSD1306Wire display;
        OLEDDisplayUi ui;
        FrameCallback frameCallbacks[1];
        NTPClient *ntpClient; 
};
#endif