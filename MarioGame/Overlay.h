#pragma once
#include <SFML/Graphics.hpp>

class Overlay
{
private:
	sf::RectangleShape overlayRect;
public:
	// Functions
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& size, const float& x, const float& y, const sf::Color& color);
};