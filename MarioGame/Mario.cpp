#include "Mario.h"
#include "Map.h"
#include <iostream>

const float movementSpeed = 10.0f; // Camera's movement speed

// Functions
void Mario::Begin()
{	
	// Init texture
	if (!texture.loadFromFile("./resources/textures/mario.png")) return;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x - sprite.getGlobalBounds().width / 2.0f, // Left
		position.y - sprite.getGlobalBounds().height,        // Top
		sprite.getGlobalBounds().width,                      // Width
		sprite.getGlobalBounds().height                      // Height
	);
}

void Mario::Update(float deltaTime)
{
	// Update texture and sprite
	sprite.setTexture(texture);

	// Update collision box
	
}

// Load Mario from file
void Mario::Draw(sf::RenderWindow &window)
{
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(1.0f / texture.getSize().x, 2.0f / texture.getSize().y));
	window.draw(sprite);
}


