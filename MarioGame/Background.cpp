#include "Background.h"
#include <iostream>

void Background::Begin(sf::RenderWindow& window, const float& zoomLevel, const Map& map)
{
	if (!texture.loadFromFile("./resources/background/sky.png"))
		return;
	sprite.setTexture(texture);

	float scaleX = (map.grid.size() / static_cast<float>(texture.getSize().x));
	float scaleY = (map.grid[0].size() / static_cast<float>(texture.getSize().y));
	sprite.setScale(scaleX, scaleY);
}

void Background::Update(sf::Vector2f position)
{
	sprite.setPosition(position);	
}

void Background::Draw(sf::RenderWindow& window)
{	
	window.draw(sprite);
}
