#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../models/WaterReading.h"
class OLEDDisplay {
public:
    OLEDDisplay();
    bool begin();
    void show(const WaterReading& reading);
private:
    void value(const char* label, float number, const char* unit);
    Adafruit_SSD1306 display_;
    bool ready_ = false;
};
