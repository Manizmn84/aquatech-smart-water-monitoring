
#pragma once

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor {
public:
    explicit TemperatureSensor(uint8_t pin);

    void begin();
    float readCelsius();

private:
    OneWire oneWire_;
    DallasTemperature sensor_;
};
