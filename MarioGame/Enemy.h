#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Map.h"
#include "FloatingScore.h"

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
	// Floating score
	FloatingScore* score;
public:
	// Constructor
	virtual ~Enemy() = default;
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

	// Setter/Getter
	sf::FloatRect getCollisionBox() const;
	bool getDieStatus() const;
	void setDieStatus(const bool& value);
	sf::Vector2f getPosition() const;
	float getDieTime();
	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f velocity);
	bool getGameState();
	void setGameState(const bool& value);
};

