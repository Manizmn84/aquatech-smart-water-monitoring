#pragma once
#include <Arduino.h>
template <size_t N> class MedianWindow {
public:
    void add(float value) { values_[index_] = value; index_ = (index_ + 1) % N; if (count_ < N) ++count_; }
    bool ready() const { return count_ == N; }
    float median() const {
        if (!count_) return NAN;
        float copy[N];
        for (size_t i = 0; i < count_; ++i) copy[i] = values_[i];
        for (size_t i = 1; i < count_; ++i) {
            float value = copy[i]; size_t j = i;
            while (j && copy[j-1] > value) { copy[j] = copy[j-1]; --j; }
            copy[j] = value;
        }
        return copy[count_/2];
    }
private:
    float values_[N] = {};
    size_t count_ = 0, index_ = 0;
};
