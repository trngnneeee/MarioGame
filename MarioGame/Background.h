#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Mario.h"
class Background
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	// Functions
	void Begin(const float& zoomLevel, const Map& map);
	void Update(const sf::Vector2f& position);
	void Draw(sf::RenderWindow& window);
};

