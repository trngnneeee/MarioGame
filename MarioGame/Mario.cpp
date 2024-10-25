#include "Mario.h"
#include "Map.h"
#include <iostream>

const float movementSpeed = 10.0f; // Camera's movement speed

// Functions
void Mario::Begin()
{	
	// Init texture
	if (!texture.loadFromFile("./resources/textures/mario.png")) return;
	sprite.setTexture(texture);

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x - sprite.getGlobalBounds().width, // Left
		position.y - sprite.getGlobalBounds().height,        // Top
		sprite.getGlobalBounds().width,                      // Width
		sprite.getGlobalBounds().height                      // Height
	);
}

void Mario::Update(float deltaTime, const Map& map)
{
	const double move = movementSpeed;

	// Update position of collision box
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	// Horizontal move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Vector2f newPosition = position;
		newPosition.x += move * deltaTime;
		collisionBox.left = newPosition.x;
		collisionBox.top = position.y;
		if (!mapCollision(map)) position.x = newPosition.x;
		facingRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Vector2f newPosition = position;
		newPosition.x-= move * deltaTime;
		collisionBox.left = newPosition.x;
		collisionBox.top = position.y;
		if (!mapCollision(map)) position.x = newPosition.x;
		facingRight = false;
	}

	// Jumping
	if (isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		verticalVelocity = -jumpStrength; // Apply upward force for jump
		isOnGround = false; // Set grounded flag to false
	}
	
	// Applying gravity
	verticalVelocity += gravity * deltaTime;
	sf::Vector2f newPosition = position;
	newPosition.y += verticalVelocity * deltaTime;

	collisionBox.left = position.x;
	collisionBox.top = newPosition.y;

	if (!mapCollision(map))
	{
		position.y = newPosition.y;
	}
	else
	{
		position.y = newPosition.y - verticalVelocity * deltaTime;
		verticalVelocity = 0;
		isOnGround = true;
	}
}

// Draw Mario to window
void Mario::Draw(sf::RenderWindow &window)
{
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(1.0f / texture.getSize().x * (facingRight ? 1 : -1), 2.0f / texture.getSize().y));
	window.draw(sprite);
}

bool Mario::mapCollision(const Map& map)
{
	for (const auto& row : map.collisionBoxList) {
		for (const auto& tileBox : row) {
			if (collisionBox.intersects(tileBox)) {
				return true; // Collision detected
			}
		}
	}
	return false; // No collision
}


