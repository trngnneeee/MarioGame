#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Mario
{
private:
	float gravity = 15.0f;
	float verticalVelocity = 0.0f;
	bool isOnGround = true;
	float jumpStrength = 8.0f;
	bool facingRight = true;
public:
	// Position
	sf::Vector2f position{};

	// Texture, Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	// Box collision
	sf::FloatRect collisionBox;

	// Functions
	void Begin();
	void Update(float deltaTime, const Map& map);
	void Draw(sf::RenderWindow& window);
	bool mapCollision(const Map& map);
};

