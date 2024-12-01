#pragma once
#include "SpeedStrategy.h"

class SuperFastSpeedStrategy : public SpeedStrategy {
public:
    float calculateSpeed(float baseSpeed) const override;
};
