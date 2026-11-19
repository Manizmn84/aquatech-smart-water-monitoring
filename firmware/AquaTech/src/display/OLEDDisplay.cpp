#include "OLEDDisplay.h"
#include <Wire.h>
#include "../config/Pins.h"
#include "../config/Settings.h"
OLEDDisplay::OLEDDisplay() : display_(128, Settings::OLED_HEIGHT, &Wire, -1) {}
bool OLEDDisplay::begin() {
    Wire.begin(Pins::OLED_SDA, Pins::OLED_SCL);
    Wire.beginTransmission(Settings::OLED_ADDRESS);
    if (Wire.endTransmission() != 0) return false;
    ready_ = display_.begin(SSD1306_SWITCHCAPVCC, Settings::OLED_ADDRESS, true, false);
    return ready_;
}
void OLEDDisplay::value(const char* label, float number, const char* unit) {
    display_.print(label);
    if (isfinite(number)) { display_.print(number, 1); display_.println(unit); }
    else display_.println("--");
}
void OLEDDisplay::show(const WaterReading& r) {
    if (!ready_) return;
    display_.clearDisplay(); display_.setTextSize(1); display_.setTextColor(SSD1306_WHITE);
    display_.setCursor(0, 0); display_.print("AquaTech");
    display_.setCursor(0, 16);
    value("Temp: ", r.temperatureC, " C");
    value("TDS*: ", r.tdsPPM, " ppm");
    value("IR: ", r.turbiditySignalMv, " mV");
    value("Turb rel: ", r.turbidityRelativePercent, "%");
    display_.println("*calibration required"); display_.display();
}
