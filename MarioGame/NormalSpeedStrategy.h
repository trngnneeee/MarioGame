// NormalSpeedStrategy.h
#pragma once
#include "SpeedStrategy.h"

class NormalSpeedStrategy : public SpeedStrategy {
public:
    float calculateSpeed(float baseSpeed) const override {
        return baseSpeed; // Không thay đổi tốc độ
    }
};