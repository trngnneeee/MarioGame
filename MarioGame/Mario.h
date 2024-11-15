#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include "Enemy.h"
#include "EnemyList.h"

class Mario
{
private:
	float gravity;
	bool isOnGround = true;
	float jumpStrength;
	sf::Vector2f velocity;
	float movementSpeed;
	bool facingRight = true;

	// Animation
	Animation runAnimation;

	// Texture, Sprite
	sf::Texture textures[5];
	sf::Sprite sprite;

	// Points (Coints)
	int points;

	// Position
	sf::Vector2f position{};
	sf::Vector2f previousPos;

	// Jump sound
	sf::Music jumpEffect;

	// Box collision
	sf::FloatRect collisionBox;

	// Dead
	float deadTimer = 1.5f;
	bool isDead;
	sf::Music deadEffect;

public:
	// Constructor
	Mario();

	// Functions
	void Begin(const sf::Vector2f& marioPosition);

	void HandleMove(float deltaTime, const Map& map);
	void HandleHorizontalMove(float deltaTime, const Map& map);
	void HandleVerticalMove(float deltaTime, const Map& map);

	void HandleDead(float deltaTime);

	void Update(float deltaTime, const Map& map, EnemyList enemies, bool& isDead);

	void updateFlip();
	void Draw(sf::RenderWindow& window);

	bool mapCollision(Map map);
	bool enemyCollison(Enemy& enemy);
	bool outOfMapCollision();

	void Reset();

	int getPoints();
	sf::Vector2f getPosition();
};