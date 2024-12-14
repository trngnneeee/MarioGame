#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "FloatingScore.h"
#include "Animation.h"
#include <string>
#include <vector> 

class HiddenBoxItem
{
protected:
	// Texture, sprite
	std::vector<sf::Texture> textures;
	sf::Sprite sprite;
	Animation animation;
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
	virtual ~HiddenBoxItem() = default;
	HiddenBoxItem();

	virtual HiddenBoxItem* clone() const = 0;

	// Functions
	virtual void Begin(sf::Vector2f mushroomPosition) = 0;
	virtual void Update(float deltaTime, const Map& map);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Reset();

	virtual void handleHorizontalMove(float deltaTime, const Map& map);
	virtual void handleVerticalMove(float deltaTime, const Map& map);
	virtual bool handleOut(float deltaTime);
	virtual bool handleDead(float deltaTime);

	// Collision
	virtual bool mapCollision(const Map& map);

	// Setter/Getter
	sf::FloatRect getCollisionBox() const;
	bool getDeadStatus();
	void setDeadStatus(const bool& value);
	float getDieTime();
	bool getOutStatus();
	sf::Vector2f getPosition();
};

