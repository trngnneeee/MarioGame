#pragma once
#include "HiddenBoxItem.h"
#include <SFML/Graphics.hpp>

class PowerUpMushroom : public HiddenBoxItem
{
private:
	
public:
	void Begin(sf::Vector2f mushroomPosition) override;
};

