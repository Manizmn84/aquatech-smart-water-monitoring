#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
class TemperatureSensor {
public:
    explicit TemperatureSensor(uint8_t pin);
    void begin();
    void update(unsigned long now);
    float readCelsius() const;
private:
    OneWire oneWire_;
    DallasTemperature sensor_;
    unsigned long requestedAt_ = 0;
    float temperature_ = NAN;
};
