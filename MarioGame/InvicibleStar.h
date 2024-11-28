#pragma once
#include <SFML/Graphics.hpp>
#include "HiddenBoxItem.h"
class InvicibleStar : public HiddenBoxItem
{
private:

public:
	void Begin(sf::Vector2f starPosition) override;
};

