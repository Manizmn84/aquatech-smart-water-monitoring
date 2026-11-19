#pragma once
#include <Arduino.h>
namespace Pins {
constexpr uint8_t TEMPERATURE = 4;
constexpr uint8_t TDS = 34;
constexpr uint8_t TURBIDITY_RECEIVER = 35;
constexpr uint8_t IR_EMITTER = 25; // Demo: GPIO -> 470 ohm -> IR LED anode; cathode -> GND.
constexpr uint8_t OLED_SDA = 21;
constexpr uint8_t OLED_SCL = 22;
}
