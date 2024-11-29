#include "Background.h"
#include <iostream>

void Background::Begin(const float& zoomLevel, const Map& map)
{
	if (!texture.loadFromFile("./resources/background/backgroundTile.png"))
		return;
	sprite.setTexture(texture);

	std::vector<std::vector<int>> grid = map.getGrid();

	float scaleX = (grid.size() / static_cast<float>(texture.getSize().x));
	float scaleY = (grid[0].size() / static_cast<float>(texture.getSize().y));
	sprite.setScale(scaleX, scaleY);
}

void Background::Update(const sf::Vector2f& position)
{
	sprite.setPosition(position);	
}

void Background::Draw(sf::RenderWindow& window)
{	
	window.draw(sprite);
}
