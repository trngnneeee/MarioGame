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
	float velocity;

	// Defeat status
	bool isDefeat;
	float dieTime;
	FloatingScore* score = NULL;
public:
	// Box collision
	sf::FloatRect collisionBox;
	
	// Position
	sf::Vector2f position{};

	// Constructors
	Enemy();
	~Enemy();

	void Begin();
	void Update(float deltaTime, const Map&, const std::vector<Enemy*>& enemies);
	void Draw(sf::RenderWindow& window);
	bool mapCollision(const Map& map);
	bool teamCollision(const Enemy& other);
	void defeatHandling();

	bool getDieStatus();
	float getDieTime();

	bool operator!=(const Enemy& other);
};