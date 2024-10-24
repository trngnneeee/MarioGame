#include "Mario.h"
#include "Map.h"
#include <iostream>

const float movementSpeed = 10.0f; // Camera's movement speed

// Functions
void Mario::Begin()
{	
}

void Mario::Update(float deltaTime, Map& map)
{
	// Horizontal Running
	float move = movementSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		move *= 2;

	// Horizontal Move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "D\n";
		sf::Vector2f newPosition = position;
		newPosition.x += move * deltaTime;
		if (!map.checkCollision(newPosition.x, newPosition.y))
			position.x = newPosition.x;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "A\n";
		sf::Vector2f newPosition = position;
		newPosition.x -= move * deltaTime;
		if (!map.checkCollision(newPosition.x, newPosition.y))
			position.x = newPosition.x;
	}

	// Jumping
	if (isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		verticalVelocity = -jumVelocity;
		isGrounded = false;
	}

	// Apply gravity
	verticalVelocity += gravity * deltaTime;
	sf::Vector2f newPosition = position;
	newPosition.y += verticalVelocity * deltaTime;

	if (map.checkCollision(newPosition.x, newPosition.y))
	{	
		// Problem
		position.y = static_cast<int>(newPosition.y);
		isGrounded = true;
		verticalVelocity = 0;
	}
	else
	{
		position.y = newPosition.y;
	}
}

// Load Mario from file
void Mario::Render(Renderer& renderer) const
{
	sf::Texture marioTexture;
	if (!marioTexture.loadFromFile("./resources/textures/mario.png")) return;
	renderer.Draw(marioTexture, position, sf::Vector2f(1.0f, 2.0f));
}

