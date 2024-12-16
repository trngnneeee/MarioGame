#include "Brick.h"

Brick::Brick()
	: isBouncing(false), bounceTime(0.0f), bounceHeight(0.3f), bounceDuration(0.1f), isBreak(false)
{
}

void Brick::Begin(const sf::Vector2f& position)
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
		if (bounceTime > bounceDuration)
		{
			isBreak = true;
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
