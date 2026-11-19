
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t pin)
    : oneWire_(pin),
      sensor_(&oneWire_) {}

void TemperatureSensor::begin() {
    sensor_.begin();
}

float TemperatureSensor::readCelsius() {
    sensor_.requestTemperatures();

    float temperature = sensor_.getTempCByIndex(0);

    if (temperature == DEVICE_DISCONNECTED_C) {
        return NAN;
    }

    return temperature;
}
