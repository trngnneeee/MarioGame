#include "Background.h"

void Background::Begin()
{
	if (!texture.loadFromFile("./resources/background/background.jpg"))
		return;
	sprite.setTexture(texture);
}

void Background::Draw(sf::RenderWindow& window, Camera camera)
{
	sprite.setPosition(camera.position);
	sprite.setScale(camera.GetViewSize().x / texture.getSize().x, camera.GetViewSize().y / texture.getSize().y);
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
	window.draw(sprite);
}
