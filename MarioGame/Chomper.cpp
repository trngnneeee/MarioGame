#include "Chomper.h"
#include <iostream>

Chomper::Chomper()
	: animation(0.2f), velocity(3.0f), isHiding(false), hidingDuration(4.0f), hidingTimer(0.0f)
{
}

void Chomper::Begin(sf::Vector2f position)
{
	this->position.y = position.y - 1.0f;
	this->position.x = position.x + 0.5f;
	minY = this->position.y;
	maxY = this->position.y + 2.0f;
	for (int i = 0; i < 2; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Chomper/chomper" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 2; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		0.8f / textures[0].getSize().x,
		1.9f / textures[0].getSize().y
	);
}

void Chomper::Update(float deltaTime)
{
	handleHiding(deltaTime);
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 2.0f / textures[0].getSize().y));
	sprite.setPosition(position);
	sprite.setTexture(*animation.update(deltaTime));
}

void Chomper::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Chomper::Reset()
{
	animation.Reset();
	textures.clear();
}

void Chomper::handleHiding(float deltaTime)
{
	if (isHiding)
	{
		hidingTimer += deltaTime;
		if (hidingTimer >= hidingDuration)
		{
			isHiding = false;
			hidingTimer = 0.0f;
			velocity = -std::abs(velocity);
			return;
		}
	}

	position.y += velocity * deltaTime;
	if (position.y >= maxY)
	{
		isHiding = true;
		position.y = maxY;
	}
	else if (position.y <= minY)
	{
		velocity = std::abs(velocity);
	}
}

sf::FloatRect Chomper::getCollisionBox() const
{
	return collisionBox;
}

bool Chomper::getHidingStatus()
{
	return isHiding;
}
