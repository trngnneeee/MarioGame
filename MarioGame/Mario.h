#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include "Goombas.h"
#include "Koopa.h"

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
	bool isDead;
	float deadTimer;
	sf::Texture deadTexture;
	float v;
	float tmpGravity;

	// Life
	int life;
public:
	// Constructor
	Mario();

	// Functions
	void Begin(const sf::Vector2f& marioPosition);

	void HandleMove(float deltaTime, Map& map);
	void HandleHorizontalMove(float deltaTime, Map& map);
	void HandleVerticalMove(float deltaTime, Map& map);
	
	void Update(float deltaTime, Map& map);

	void updateFlip();
	void Draw(sf::RenderWindow& window);

	bool mapCollision(Map& map);
	bool outOfMapCollision();
	bool goombasCollision(Goombas& goombas);
	bool koopaCollision(Koopa& koopa);

	void Reset();

	// Getter/Setter
	int getPoints();
	void setPoints(const int& n);

	bool getDeadStatus();
	void setDeadStatus(const bool& value);

	float getDeadTimer();

	sf::Vector2f getPosition();

	int getLife();
	void setLife(const int& n);
};