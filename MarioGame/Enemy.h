#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Map.h"

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

public:
	// Box collision
	sf::FloatRect collisionBox;

	// Constructors
	Enemy();

	// Position
	sf::Vector2f position{};

	void Begin();
	void Update(float deltaTime, const Map&, const std::vector<Enemy>& enemies);
	void Draw(sf::RenderWindow& window);
	bool mapCollision(const Map& map);
	bool teamCollision(const Enemy& other);

	bool operator!=(const Enemy& other);
};