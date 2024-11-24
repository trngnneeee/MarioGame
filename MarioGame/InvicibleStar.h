#pragma once
#include <SFML/Graphics.hpp>
#include "PowerUpMushroom.h"
class InvicibleStar : public PowerUpMushroom
{
private:

public:
	void Begin(sf::Vector2f starPosition);
};

