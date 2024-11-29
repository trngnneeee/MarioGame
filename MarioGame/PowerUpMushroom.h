#pragma once
#include "HiddenBoxItem.h"
#include <SFML/Graphics.hpp>

class PowerUpMushroom : public HiddenBoxItem
{
private:
	
public:
	PowerUpMushroom* clone() const override {
		return new PowerUpMushroom(*this); 
	}
	void Begin(sf::Vector2f mushroomPosition) override;
};

