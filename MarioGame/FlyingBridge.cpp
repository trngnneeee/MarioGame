#include "FlyingBridge.h"
#include <iostream>

FlyingBridge::FlyingBridge()
	: velocity(sf::Vector2f(0.0f, 3.0f)), maxRange(13.0f), minRange(6.0f)
{
}

void FlyingBridge::Begin(const sf::Vector2f& position)
{
	texture.loadFromFile("./resources/textures/bridge.png");
	sprite.setTexture(texture);
	this->position = position;
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		3.0f / texture.getSize().x,
		0.5f / texture.getSize().y
	);
}

void FlyingBridge::Update(const float& deltaTime)
{
	position.y += velocity.y * deltaTime;
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	if (position.y >= maxRange || position.y <= minRange)
	{
		velocity.y = -velocity.y;
	}
}

void FlyingBridge::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(3.0f / texture.getSize().x, 0.5f / texture.getSize().y));
	window.draw(sprite);
}

sf::FloatRect FlyingBridge::getCollisionBox() const
{
	return collisionBox;
}

sf::Vector2f FlyingBridge::getVelocity() const
{
	return velocity;
}
