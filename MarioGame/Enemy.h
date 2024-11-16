#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include "Animation.h"
#include "Map.h"
#include "FloatingScore.h"

class Enemy
{
private:
	// Texture, sprite
	sf::Texture texture[2];
	sf::Sprite sprite;

	// Animation
	Animation runAnimation;

	// Horizontal velocity
	sf::Vector2f velocity;
	float gravity;

	// Defeat status
	bool isDefeat;
	float dieTime;
	FloatingScore* score = NULL;
	
	// Box collision
	sf::FloatRect collisionBox;
	
	// Position
	sf::Vector2f position{};
public:
	// Constructors
	Enemy();
	~Enemy();

	void Begin();

	void Update(float deltaTime, const Map&);
	void handleMove(float deltaTime, const Map& map);
	void handleHorizontalMove(float deltaTime, const Map& map);
	void handleVerticalMove(float deltaTime, const Map& map);

	void UpdateTextures(float deltaTime);
	void handleDefeat();

	void Draw(sf::RenderWindow& window);

	bool mapCollision(const Map& map);
	bool teamCollision(const Enemy& other);
	bool outOfMapCollision();

	bool getDieStatus();
	float getDieTime();

	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);

	sf::FloatRect& getCollisionBox();

	bool operator!=(const Enemy& other);
};