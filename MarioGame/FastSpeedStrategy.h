#pragma once
#include "SpeedStrategy.h"

class FastSpeedStrategy : public SpeedStrategy {
public:
    float calculateSpeed(float baseSpeed) const override {
        return baseSpeed * 1.5f; // Tăng tốc độ lên 1.5 lần
    }
};