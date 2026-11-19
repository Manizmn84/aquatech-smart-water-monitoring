#pragma once
#include <Arduino.h>
namespace Settings {
constexpr uint8_t OLED_ADDRESS = 0x3C;
constexpr uint8_t OLED_HEIGHT = 64;
constexpr uint32_t REPORT_INTERVAL_MS = 1000;
constexpr float TDS_GAIN = 1.0f; // Reference ppm / uncalibrated ppm at reference solution.
// Set both after measuring fixed-geometry clear and turbid reference samples.
// These define a relative scale, never NTU.
constexpr float TURBIDITY_CLEAR_MV = NAN;
constexpr float TURBIDITY_REFERENCE_MV = NAN;
}
