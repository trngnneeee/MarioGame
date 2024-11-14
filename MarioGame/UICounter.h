#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Mario.h"

class UICounter
{
private:
	sf::Font font;
	sf::Text prompt;
public:
	UICounter();

	void Begin();
	void Update(Camera camera, const int& points);
	void Draw(sf::RenderWindow& window);
};

