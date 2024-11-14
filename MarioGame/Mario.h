#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include "Enemy.h"

class Mario
{
private:
	float gravity = 40.0f;
	bool isOnGround = true;
	float jumpStrength = 18.0f;
	bool facingRight = true;

	float verticalVelocity = 0.0f;
	double horizontalVelocity = 0.0f;

	// Animation
	Animation runAnimation;

	// Texture, Sprite
	sf::Texture textures[5];
	sf::Sprite sprite;

	// Points (Coints)
	int points;
public:
	// Position
	sf::Vector2f position{};
	sf::Vector2f previousPos;

	// Overlay
	sf::RectangleShape overlayRect;

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
	bool mapCollision(Map map);
	bool enemyCollison(Enemy& enemy);
	void Reset();

	int getPoints();
};