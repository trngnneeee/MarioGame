#pragma once
#include <SFML/Graphics.hpp>
#include "HiddenBoxItem.h"
class FireFlower : public HiddenBoxItem
{
private:

public:
	FireFlower* clone() const override {
		return new FireFlower(*this);
	}
	void Begin(sf::Vector2f flowerPosition) override;
};

