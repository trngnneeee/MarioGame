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

	// Points 
	int points;
	int coins;
	// Position
	sf::Vector2f position{};
	sf::Vector2f previousPos;

	// Jump sound
	sf::Music jumpEffect;

	// Box collision
	sf::FloatRect collisionBox;

	// Dead
	float deadTimer;
	bool isDead;
	sf::Texture deadTexture;

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

	void HandleDead(float deltaTime);

	void Update(float deltaTime, Map& map, EnemyList enemies, bool& isDead, sf::Music& music);

	void updateFlip();
	void Draw(sf::RenderWindow& window);

	bool mapCollision(Map& map);
	bool enemyCollison(Enemy& enemy);
	bool outOfMapCollision();

	void Reset();

	int& getPoints();
	void setPoints(const int& n);
	
	int& getCoins();
	void setCoins(const int& n);
	sf::Vector2f getPosition();

	int getLife();
	void setLife(const int& n);
	sf::FloatRect getCollisionBox() const;
};