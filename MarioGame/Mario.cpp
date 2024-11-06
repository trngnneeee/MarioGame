#include "Mario.h"
#include "Map.h"
#include "Overlay.h"
#include <iostream>

const float movementSpeed = 10.0f; // Camera's movement speed

Mario::Mario()
	: runAnimation(0.3f)
{
}

Overlay marioOverlay;

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
		position.x,
		position.y,       
		1.0f / textures[3].getSize().x,
		1.9f / textures[3].getSize().y
	);
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
		verticalVelocity = -jumpStrength;
		isOnGround = false; 
		jumpEffect.play();
	}

	// Update animation
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

	// Vertical collision check
	if (!mapCollision(map))
	{
		position.y = newPosition.y;
	}
	else {
		if (verticalVelocity > 0) {
			position.y = newPosition.y - verticalVelocity * deltaTime;
			verticalVelocity = 0; 
			isOnGround = true;
		}
		else if (verticalVelocity < 0) {
			position.y = newPosition.y - verticalVelocity * deltaTime;
			verticalVelocity = 0; 
		}
	}

	// Update overlay (Optional)
	marioOverlay.Update(sf::Vector2f(collisionBox.width, collisionBox.height), position.x, position.y, sf::Color (255, 0, 0, 100));
}

// Draw Mario to window
void Mario::Draw(sf::RenderWindow &window)
{
	// Flip mario if change position horizontally
	if (facingRight) {
		sprite.setOrigin(0, 0);  // Left-center for right-facing
	}
	else {
		sprite.setOrigin(textures[3].getSize().x, 0); // Right-center for left-facing
	}
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(0.7f / textures[3].getSize().x * (facingRight ? 1 : -1), 1.9f / textures[3].getSize().y));
	window.draw(sprite);

	// Draw overlay (Comment this to unactive the overlay)
	//marioOverlay.Draw(window);
}

bool Mario::mapCollision(const Map& map)
{
	// Collision for brick only
	for (int i = 0; i < map.collisionBoxList.size(); i++)
	{
		for (int j = 0; j < map.collisionBoxList[i].size(); j++)
		{
			if (collisionBox.intersects(map.collisionBoxList[i][j]) && (map.grid[i][j] == 1 || map.grid[i][j] == 2 || map.grid[i][j] == 4))
				return true;
		}
	}
	return false; // No collision

	/*return (map.collisionBoxList[position.x / map.cellSize][position.y / map.cellSize].intersects(collisionBox));*/

}


