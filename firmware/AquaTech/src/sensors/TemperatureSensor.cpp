#include "TemperatureSensor.h"
TemperatureSensor::TemperatureSensor(uint8_t pin) : oneWire_(pin), sensor_(&oneWire_) {}
void TemperatureSensor::begin() {
    sensor_.begin(); sensor_.setResolution(12); sensor_.setWaitForConversion(false);
    sensor_.requestTemperatures(); requestedAt_ = millis();
}
void TemperatureSensor::update(unsigned long now) {
    if (now - requestedAt_ < 750) return;
    float t = sensor_.getTempCByIndex(0);
    temperature_ = t != DEVICE_DISCONNECTED_C && isfinite(t) && t >= -55 && t <= 125 ? t : NAN;
    sensor_.requestTemperatures(); requestedAt_ = now;
}
float TemperatureSensor::readCelsius() const { return temperature_; }
