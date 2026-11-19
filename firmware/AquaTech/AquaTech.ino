
#include <Arduino.h>
#include <math.h>

#include "src/config/Pins.h"
#include "src/sensors/TemperatureSensor.h"

TemperatureSensor temperatureSensor(Pins::TEMPERATURE);

void setup() {
    Serial.begin(115200);

    temperatureSensor.begin();

    Serial.println("AquaTech initialized!");
}

void loop() {
    float temperature = temperatureSensor.readCelsius();

    if (isnan(temperature)) {
        Serial.println("Temperature sensor disconnected!");
    } else {
        Serial.print("Water temperature: ");
        Serial.print(temperature);
        Serial.println(" C");
    }

    delay(1000);
}
