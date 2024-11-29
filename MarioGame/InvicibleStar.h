#pragma once
#include <SFML/Graphics.hpp>
#include "HiddenBoxItem.h"
class InvicibleStar : public HiddenBoxItem
{
private:

public:
	InvicibleStar* clone() const override {
		return new InvicibleStar(*this);
	}
	void Begin(sf::Vector2f starPosition) override;
};

