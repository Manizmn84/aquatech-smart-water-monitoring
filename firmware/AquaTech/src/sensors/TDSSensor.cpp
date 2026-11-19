#include "TDSSensor.h"
#include "../config/Settings.h"
void TDSSensor::begin() { pinMode(pin_, INPUT); analogSetPinAttenuation(pin_, ADC_11db); }
void TDSSensor::update(unsigned long now) {
    if (now - lastSample_ < 40) return;
    lastSample_ = now;
    samples_.add(analogReadMilliVolts(pin_));
}
float TDSSensor::voltage() const { return samples_.ready() ? samples_.median()/1000.0f : NAN; }
float TDSSensor::readPPM(float temperatureC) const {
    float v = voltage();
    if (!isfinite(v) || v < 0 || v > 2.3f || !isfinite(temperatureC) || temperatureC < 0 || temperatureC > 55) return NAN;
    v /= 1.0f + 0.02f * (temperatureC - 25.0f);
    // CQRobot CQRSENTDS01 Arduino example; calibrated millivolts replace UNO ADC conversion.
    float ppm = (133.42f*v*v*v - 255.86f*v*v + 857.39f*v)*0.5f*Settings::TDS_GAIN;
    return isfinite(ppm) && ppm >= 0 && ppm <= 1000 ? ppm : NAN;
}
