#include "Flag.h"

void Flag::Begin(const sf::Vector2f& position)
{
	texture.loadFromFile("./resources/textures/flag.png");
	sprite.setTexture(texture);
	this->position = position;
	this->position.y += 1.0f;
	this->position.x -= 0.5f;
}

void Flag::Update(const float& deltaTime)
{
	position.y += 5.0f * deltaTime;
}

void Flag::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(1.0f / texture.getSize().x, 1.0f / texture.getSize().y));
	window.draw(sprite);
}

void Flag::setPosition(const sf::Vector2f& position)
{
	this->position = position;
}
