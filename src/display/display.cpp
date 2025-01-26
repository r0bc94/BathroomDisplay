#include "display.hpp"


Display::Display(DISPLAYCONFIG *config) : 
    displayconfig(config),
    display(SSD1306Wire(0x3c, config->sda_pin, config->sdc_pin)),
    ui(OLEDDisplayUi(&display)) {
}

bool Display::initialize() {
    this->frameCallbacks[0] = digitalClockFrame;

    this->display.setBrightness(255);
    this->display.setContrast(255);

    // The ESP is capable of rendering 60fps in 80Mhz mode
    // but that won't give you much time for anything else
    // run it in 160Mhz mode or just set it to 30 fps
    ui.setTargetFPS(30);

    // Customize the active and inactive symbol
    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);

    // You can change this to
    // TOP, LEFT, BOTTOM, RIGHT
    ui.setIndicatorPosition(BOTTOM);

    // Defines where the first frame is located in the bar.
    ui.setIndicatorDirection(LEFT_RIGHT);

    // You can change the transition that is used
    // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
    ui.setFrameAnimation(SLIDE_LEFT);

    // Add frames
    ui.setFrames(this->frameCallbacks, NUMBER_OF_FRAMES);

    // Initialising the UI will init the display too.
    ui.init();

    Serial.println("Display Initialized");
    return true;

}

unsigned int Display::update() {
    this->ui.getUiState()->userData = this->ntpClient;
    return this->ui.update();
}

SSD1306Wire& Display::getDisplay() {
    return this->display;
}

void Display::setNTPClient(NTPClient *ntpclient) {
    this->ntpClient = ntpclient;
}

void Display::displayWelcomeFrame() {
    String msg = "Roberts Bathroom Display";
    this->display.setFont(ArialMT_Plain_10);
    uint8_t width = this->display.getStringWidth(msg);
    this->display.drawString(64 - (width / 2), 20, msg);

    this->display.setFont(ArialMT_Plain_10);
    this->display.drawString(0, 50, "v0.0.1");
    this->display.display();
}

void digitalClockFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  NTPClient *ntpclient = (NTPClient*) state->userData;
  String ntptime = ntpclient->getFormattedTime();
  time_t epoch = ntpclient->getEpochTime();
  struct tm *timeInfo = localtime(&epoch);

  // Draw Clock
  // display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_24);
  uint8_t width = display->getStringWidth(ntptime);
  display->drawString(64 - (width / 2), 10, ntptime);

  // Draw Date
  char datebuff[20];
  sprintf(datebuff, "%02d.%02d.%04d", timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year);
  display->setFont(ArialMT_Plain_10);
  width = display->getStringWidth(datebuff);
  display->drawString(64 - (width / 2), 35, datebuff);
}

