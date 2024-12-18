#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Map.h"
#include "FloatingScore.h"
#include "SpeedStrategy.h"
#include "Bullet.h"

class Enemy
{
protected:
	// Animation
	Animation runAnimation;
	// Gravity
	float gravity;
	// Texture, sprite
	std::vector<sf::Texture> textures;
	sf::Sprite sprite;
	// Velocity
	sf::Vector2f velocity;
	// Dead status
	bool isDead;
	float dieTime;
	// Value for dead animation
	float v;
	float tmpGravity;
	// State
	bool inGame;
	// Position
	sf::Vector2f position;
	// Collision box
	sf::FloatRect collisionBox;
	sf::Texture deadTexture;
	// Speed Strategy
	SpeedStrategy* speedStrategy;
	float baseSpeed;
	// Added Floating Score
	bool addedFloatingScore;
public:
	// Constructor
	virtual ~Enemy() { delete speedStrategy; }
	virtual Enemy* clone() const = 0;

	Enemy();

	// Functions
	virtual void Begin(const sf::Vector2f& position) = 0;
	virtual void Update(float deltaTime, const Map& map) = 0;
	virtual void Draw(sf::RenderWindow& window);
	void Reset();

	virtual void handleHorizontalMove(float deltaTime, const Map& map);
	virtual void handleVerticalMove(float deltaTime, const Map& map);

	// Collision
	bool mapCollision(const Map& map);
	bool bulletCollision(const Bullet& bullet);

	// Setter/Getter
	sf::FloatRect getCollisionBox() const;
	bool getDieStatus() const;
	void setDieStatus(const bool& value);
	sf::Vector2f getPosition() const;
	float getDieTime();
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& velocity);
	bool getGameState();
	void setGameState(const bool& value);
	float getSpeedStrategy() const;
	void setSpeedStrategy(SpeedStrategy* strategy);
	bool getAddedFloatingScore() const;
	void setAddedFloatingScore(const bool& value);
};