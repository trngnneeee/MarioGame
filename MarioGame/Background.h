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
	void Begin(sf::RenderWindow& window, const float& zoomLevel);
	void Update(sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
};

