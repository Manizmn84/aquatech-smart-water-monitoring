#pragma once
#include <Arduino.h>
#include <math.h>
struct WaterReading {
    float temperatureC = NAN;
    float tdsPPM = NAN;
    float tdsVoltage = NAN;
    float turbiditySignalMv = NAN;
    float turbidityRelativePercent = NAN;
    unsigned long timestampMs = 0;
};
