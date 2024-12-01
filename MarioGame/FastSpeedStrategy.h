#pragma once
#include "SpeedStrategy.h"
class FastSpeedStrategy : public SpeedStrategy {
public:
    float calculateSpeed(float baseSpeed) const override;
};

