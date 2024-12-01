// SpeedStrategy.h
#pragma once

class SpeedStrategy {
public:
    virtual ~SpeedStrategy() = default;
    virtual float calculateSpeed(float baseSpeed) const = 0;
};
