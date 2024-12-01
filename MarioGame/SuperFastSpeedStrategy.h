#pragma once
#include "SpeedStrategy.h"

class SuperFastSpeedStrategy : public SpeedStrategy {
public:
    float calculateSpeed(float baseSpeed) const override {
        return baseSpeed * 2.0f; // Tăng tốc độ lên 2 lần
    }
};