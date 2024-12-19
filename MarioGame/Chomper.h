#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Bullet.h"
#include "FloatingScore.h"
class Chomper
{
private:
	sf::Sprite sprite;
	std::vector<sf::Texture> textures;
	Animation animation;
	sf::Vector2f position;
	float minY;
	float maxY;
	float velocity;
	bool isHiding;                
	float hidingTimer;            
	float hidingDuration;
	sf::FloatRect collisionBox;
	bool isDead;
	FloatingScore* score;
public:
	// Constructors
	Chomper();
	// Functions
	void Begin(sf::Vector2f position);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	void handleHiding(float deltaTime);
	bool bulletCollision(const Bullet& bullet);
	// Setters/Getters
	sf::FloatRect getCollisionBox() const;
	bool getHidingStatus();
	bool getDeadStatus();
	void setDeadStatus(const bool& value);
	sf::Vector2f getPosition() const;
};

