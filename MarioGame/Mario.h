#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"

class Mario
{
private:
	float gravity = 15.0f;
	float verticalVelocity = 0.0f;
	bool isOnGround = true;
	float jumpStrength = 10.0f;
	bool facingRight = true;
	double horizontalVelocity = 0.0f;

	// Animation
	Animation runAnimation;
public:
	// Position
	sf::Vector2f position{};
	sf::Vector2f previousPos;

	// Texture, Sprite
	sf::Texture textures[5];
	sf::Sprite sprite;

	// Jump sound
	sf::Music jumpEffect;

	// Box collision
	sf::FloatRect collisionBox;
	
	// Constructor
	Mario();

	// Functions
	void Begin();
	void Update(float deltaTime, const Map& map);
	void Draw(sf::RenderWindow& window);
	bool mapCollision(const Map& map);
};