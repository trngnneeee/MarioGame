#pragma once
#include "SpeedStrategy.h"
class NormalSpeedStrategy : public SpeedStrategy
{
    float calculateSpeed(float baseSpeed) const override;
};

