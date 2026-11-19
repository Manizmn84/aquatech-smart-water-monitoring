#include <Arduino.h>
#include "src/config/Pins.h"
#include "src/config/Settings.h"
#include "src/models/WaterReading.h"
#include "src/sensors/TemperatureSensor.h"
#include "src/sensors/TDSSensor.h"
#include "src/sensors/TurbiditySensor.h"
#include "src/display/OLEDDisplay.h"
TemperatureSensor temperatureSensor(Pins::TEMPERATURE);
TDSSensor tdsSensor(Pins::TDS);
TurbiditySensor turbiditySensor(Pins::TURBIDITY_RECEIVER, Pins::IR_EMITTER);
OLEDDisplay oled;
unsigned long lastReport = 0;
void setup() {
    Serial.begin(115200);
    analogReadResolution(12);
    temperatureSensor.begin(); tdsSensor.begin(); turbiditySensor.begin();
    if (!oled.begin()) Serial.println("OLED unavailable; continuing with Serial.");
    Serial.println("AquaTech: TDS requires calibration; turbidity is relative, not NTU.");
    Serial.println("ms,temp_C,tds_ppm,tds_V,ir_delta_mV,turbidity_relative_pct");
}
void loop() {
    unsigned long now = millis();
    temperatureSensor.update(now); tdsSensor.update(now); turbiditySensor.update(now);
    if (now - lastReport < Settings::REPORT_INTERVAL_MS) return;
    lastReport = now;
    WaterReading r;
    r.timestampMs = now; r.temperatureC = temperatureSensor.readCelsius();
    r.tdsVoltage = tdsSensor.voltage(); r.tdsPPM = tdsSensor.readPPM(r.temperatureC);
    r.turbiditySignalMv = turbiditySensor.signalMv();
    r.turbidityRelativePercent = turbiditySensor.relativePercent();
    Serial.print(r.timestampMs); Serial.print(','); Serial.print(r.temperatureC, 2);
    Serial.print(','); Serial.print(r.tdsPPM, 1); Serial.print(','); Serial.print(r.tdsVoltage, 3);
    Serial.print(','); Serial.print(r.turbiditySignalMv, 1); Serial.print(','); Serial.println(r.turbidityRelativePercent, 1);
    oled.show(r);
}
