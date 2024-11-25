#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "FloatingScore.h"

class PowerUpMushroom
{
protected:
	// Texture, sprite
	sf::Texture texture;
	sf::Sprite sprite;
	// Position
	sf::Vector2f position;
	float hiddenBoxPosition; // static value to keep track the hidden box position
	bool isOut;
	// Velocity
	sf::Vector2f velocity;
	// Gravity
	float gravity;
	// Collision box
	sf::FloatRect collisionBox;
	// Dead
	bool isDead;
	float dieTime;
	// Floating score
	FloatingScore* score;
public:
	// Constructor
	PowerUpMushroom();

	// Functions
	void Begin(sf::Vector2f mushroomPosition);

	void handleHorizontalMove(float deltaTime, const Map& map);
	void handleVerticalMove(float deltaTime, const Map& map);

	void Update(float deltaTime, const Map& map);
	void Draw(sf::RenderWindow& window);

	bool mapCollision(const Map& map);
	// Setter/Getter
	sf::FloatRect getCollisionBox() const;

	bool getDeadStatus();
	void setDeadStatus(const bool& value);

	float getDieTime();

	bool getOutStatus();
};

