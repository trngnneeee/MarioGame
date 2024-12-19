#include "Brick.h"
#include <iostream>

Brick::Brick()
	: isBouncing(false), bounceTime(0.0f), bounceHeight(0.3f), bounceDuration(0.4f), isBreak(false), durability(1)
{
}

void Brick::Begin(const sf::Vector2f& position, int durability)
{
	texture.loadFromFile("./resources/textures/brick.png");
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(1.0f / texture.getSize().x, 1.0f / texture.getSize().y));
	this->position = position;
	startPosition = this->position;
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f,
		1.0f
	);
	this->durability = durability;
}

void Brick::Update(const float& deltaTime)
{
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	HandleBounceUp(deltaTime);
}

void Brick::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Brick::HandleBounceUp(const float& deltaTime)
{
	if (isBouncing)
	{
		bounceTime += deltaTime;

		if (bounceTime <= bounceDuration / 2.0f)
		{
			position.y = startPosition.y - bounceHeight * (bounceTime / (bounceDuration / 2.0f));
		}
		else if (bounceTime <= bounceDuration)
		{
			if (durability == 1)
			{
				isBreak = true;
				return;
			}
			position.y = startPosition.y - bounceHeight * (1.0f - (bounceTime - bounceDuration / 2.0f) / (bounceDuration / 2.0f));
		}
		else if (bounceTime > bounceDuration)
		{
			bounceTime = 0.0f;
			if (durability > 0)
			{
				durability--;
				isBouncing = false;
			}
		}
	}
}

bool Brick::getBounceStatus() const
{
	return isBouncing;
}

void Brick::setBounceStatus(const bool& value)
{
	isBouncing = value;
}

bool Brick::getBrokeStatus() const
{
	return isBreak;
}

sf::FloatRect Brick::getCollisionBox() const
{
	return collisionBox;
}

sf::Vector2f Brick::getPosition() const
{
	return position;
}

sf::Vector2f Brick::getStartPosition() const
{
	return startPosition;
}

int Brick::getDurability() const
{
	return durability;
}