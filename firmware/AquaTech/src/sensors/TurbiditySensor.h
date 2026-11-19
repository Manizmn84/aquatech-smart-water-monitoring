#pragma once
#include "../utils/MedianWindow.h"
class TurbiditySensor {
public:
    TurbiditySensor(uint8_t receiver, uint8_t emitter) : receiver_(receiver), emitter_(emitter) {}
    void begin();
    void update(unsigned long now);
    float signalMv() const;
    float relativePercent() const;
private:
    uint8_t receiver_, emitter_;
    bool illuminated_ = false;
    unsigned long changedAt_ = 0;
    float darkMv_ = 0;
    MedianWindow<15> samples_;
};
