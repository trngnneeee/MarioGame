#include "HiddenBox.h"
#include <iostream>

HiddenBox::HiddenBox()
	: animation(1.5f), used(false), isBouncing(false), bounceTime(0.0f), bounceHeight(0.3f), bounceDuration(0.4f)
{
}

void HiddenBox::Begin(const sf::Vector2f& position)
{
	for (int i = 0; i < 3; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/HiddenBox/hiddenbox" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 3; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.5f * (i + 1)));
	}
	usedTexture.loadFromFile("./resources/textures/block.png");
	this->position = position;
	startPosition = this->position;
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f,
		1.0f
	);
}

void HiddenBox::Update(const float& deltaTime)
{
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	HandleBounceUp(deltaTime);
	if (used) sprite.setTexture(usedTexture);
	else sprite.setTexture(*animation.update(deltaTime));
	sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
}

void HiddenBox::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void HiddenBox::Reset()
{
	animation.Reset();
	textures.clear();
}

void HiddenBox::HandleBounceUp(const float& deltaTime)
{
	if (isBouncing)
	{
		bounceTime += deltaTime;
		sprite.setTexture(textures[0]);

		if (bounceTime <= bounceDuration / 2.0f)
		{
			position.y = startPosition.y - bounceHeight * (bounceTime / (bounceDuration / 2.0f));
		}
		else if (bounceTime <= bounceDuration)
		{
			position.y = startPosition.y - bounceHeight * (1.0f - (bounceTime - bounceDuration / 2.0f) / (bounceDuration / 2.0f));
		}
		else
		{
			position.y = startPosition.y;
			isBouncing = false;
			used = true;
		}
	}
}

sf::FloatRect HiddenBox::getCollisionBox() const
{
	return collisionBox;
}

sf::Vector2f HiddenBox::getPosition() const
{
	return position;
}

bool HiddenBox::getUsedStatus() const
{
	return used;
}

void HiddenBox::setUsedStatus(const bool& value)
{
	used = value;
}

bool HiddenBox::getBounceStatus() const
{
	return isBouncing;
}

void HiddenBox::setBounceStatus(const bool& value)
{
	isBouncing = value;
}

float HiddenBox::getBounceHeight() const
{
	return bounceHeight;
}
