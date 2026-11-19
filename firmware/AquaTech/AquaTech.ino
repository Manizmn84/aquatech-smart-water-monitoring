
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("AquaTech initialized!");
}

void loop() {
    Serial.println("AquaTech is running...");
    delay(1000);
}
