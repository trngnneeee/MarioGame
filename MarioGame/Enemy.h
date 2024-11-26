#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Map.h"
#include "FloatingScore.h"

class Enemy
{
protected:
	// Texture, sprite
	std::vector<sf::Texture> textures;
	sf::Sprite sprite;
	// Animation
	Animation runAnimation;
	// Position
	sf::Vector2f position;
	// Collision box
	sf::FloatRect collisionBox;
	// Velocity
	sf::Vector2f velocity;
	// Gravity
	float gravity;
	// Dead status
	bool isDead;
	float dieTime;
	sf::Texture deadTexture;
	// Floating score
	FloatingScore* score;
	// Value for dead animation
	float v;
	float tmpGravity;
	// State
	bool inGame;
public:
	// Constructor
	Enemy();

	void Begin();

	void handleHorizontalMove(float deltaTime, const Map& map);
	void handleVerticalMove(float deltaTime, const Map& map);
	void Update(float deltaTime, const Map& map);
	void Draw(sf::RenderWindow& window);
	
	bool mapCollision(const Map& map);

	void Reset();

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

