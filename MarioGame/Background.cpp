#include "Background.h"

void Background::Begin(sf::RenderWindow& window, const float& zoomLevel)
{
	if (!texture.loadFromFile("./resources/background/background.jpg"))
		return;
	sprite.setTexture(texture);
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
	float scaleX = (window.getSize().x / static_cast<float>(texture.getSize().x)) * zoomLevel;
	float scaleY = (window.getSize().y / static_cast<float>(texture.getSize().y)) * zoomLevel;
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
