#pragma once
#include "../utils/MedianWindow.h"
class TDSSensor {
public:
    explicit TDSSensor(uint8_t pin) : pin_(pin) {}
    void begin();
    void update(unsigned long now);
    float voltage() const;
    float readPPM(float temperatureC) const;
private:
    uint8_t pin_;
    unsigned long lastSample_ = 0;
    MedianWindow<31> samples_;
};
