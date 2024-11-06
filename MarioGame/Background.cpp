#include "Background.h"

void Background::Begin()
{
	if (!texture.loadFromFile("./resources/background/background.jpg"))
		return;
	sprite.setTexture(texture);
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f); 
	
}

void Background::Update(Camera camera)
{
	sprite.setScale(camera.GetViewSize().x / texture.getSize().x, camera.GetViewSize().y / texture.getSize().y);
	sprite.setPosition(camera.position);
	
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
