#include "FlyingBridge.h"
#include <iostream>

FlyingBridge::FlyingBridge(const sf::Vector2f& velocity, const float& maxRangeX, const float& minRangeX, const float& maxRangeY, const float& minRangeY)
{
	this->velocity = velocity;
	this->maxRangeX = maxRangeX;
	this->minRangeX = minRangeX;
	this->maxRangeY = maxRangeY;
	this->minRangeY = minRangeY;
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
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	position.y += velocity.y * deltaTime;
	if (position.y >= maxRangeY || position.y <= minRangeY)
	{
		velocity.y = -velocity.y;
	}
	position.x += velocity.x * deltaTime;
	if (position.x >= maxRangeX || position.x <= minRangeX)
	{
		velocity.x = -velocity.x;
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
