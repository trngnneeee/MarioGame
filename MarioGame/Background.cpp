#include "Background.h"

void Background::Begin()
{
	if (!texture.loadFromFile("./resources/background/sky.png"))
		return;
	sprite.setTexture(texture);
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f); 
}

void Background::Update(Camera camera, sf::Vector2f position)
{
	sprite.setScale(camera.GetViewSize().x / texture.getSize().x, camera.GetViewSize().y / texture.getSize().y);
	sprite.setPosition(position);	
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
