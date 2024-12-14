#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
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
public:
	// Constructors
	Chomper();
	// Functions
	void Begin(sf::Vector2f position);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	void handleHiding(float deltaTime);
	// Setters/Getters
	sf::FloatRect getCollisionBox() const;
	bool getHidingStatus();
};

