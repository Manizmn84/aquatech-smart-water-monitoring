#include "TurbiditySensor.h"
#include "../config/Settings.h"
void TurbiditySensor::begin() {
    pinMode(emitter_, OUTPUT); digitalWrite(emitter_, LOW);
    pinMode(receiver_, INPUT); analogSetPinAttenuation(receiver_, ADC_11db);
    changedAt_ = millis();
}
void TurbiditySensor::update(unsigned long now) {
    if (now - changedAt_ < 10) return; // Initial settling time; tune after circuit validation.
    changedAt_ = now;
    float mv = analogReadMilliVolts(receiver_);
    if (!illuminated_) { darkMv_ = mv; illuminated_ = true; }
    else { samples_.add(mv - darkMv_); illuminated_ = false; }
    digitalWrite(emitter_, illuminated_ ? HIGH : LOW);
}
float TurbiditySensor::signalMv() const { return samples_.ready() ? samples_.median() : NAN; }
float TurbiditySensor::relativePercent() const {
    float signal = signalMv();
    float span = Settings::TURBIDITY_REFERENCE_MV - Settings::TURBIDITY_CLEAR_MV;
    if (!isfinite(signal) || !isfinite(span) || fabsf(span) < 1) return NAN;
    float percent = 100*(signal - Settings::TURBIDITY_CLEAR_MV)/span;
    return constrain(percent, 0.0f, 100.0f);
}
