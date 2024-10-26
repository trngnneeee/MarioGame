#include "Mario.h"
#include "Map.h"
#include <iostream>

const float movementSpeed = 10.0f; // Camera's movement speed

Mario::Mario()
	: runAnimation(0.3f)
{
}

// Functions
void Mario::Begin()
{	
	// Init texture
	if (!textures[0].loadFromFile("./resources/textures/run1.png"))
		return;
	if (!textures[1].loadFromFile("./resources/textures/run2.png"))
		return;
	if (!textures[2].loadFromFile("./resources/textures/run3.png"))
		return;
	if (!textures[3].loadFromFile("./resources/textures/mario.png"))
		return;
	if (!textures[4].loadFromFile("./resources/textures/jump.png"))
		return;

	runAnimation.addFrame(Frame(&textures[0], 0.1f));
	runAnimation.addFrame(Frame(&textures[1], 0.2f));
	runAnimation.addFrame(Frame(&textures[2], 0.3f));

	// Init jump sound
	if (!jumpEffect.openFromFile("./resources/soundEffect/jump.wav"))
		return;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x - sprite.getGlobalBounds().width, // Left
		position.y - sprite.getGlobalBounds().height,        // Top
		sprite.getGlobalBounds().width,                      // Width
		sprite.getGlobalBounds().height                      // Height
	);

	// Init previous position
	previousPos = position;
}

void Mario::Update(float deltaTime, const Map& map)
{
	const double move = movementSpeed;

	// Update previous position
	previousPos = position;

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

	// Calculate horizontal velocity
	horizontalVelocity = (position.x - previousPos.x) / deltaTime;

	// Jumping
	if (isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		verticalVelocity = -jumpStrength; // Apply upward force for jump
		isOnGround = false; // Set grounded flag to false
		jumpEffect.play();
	}

	if (!isOnGround)
		sprite.setTexture(textures[4]);
	else if (horizontalVelocity != 0)
		sprite.setTexture(*runAnimation.update(deltaTime));
	else sprite.setTexture(textures[3]);
	
	
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
	sprite.setOrigin((sf::Vector2f)textures[3].getSize() / 2.0f);
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(1.0f / textures[3].getSize().x * (facingRight ? 1 : -1), 2.0f / textures[3].getSize().y));
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


