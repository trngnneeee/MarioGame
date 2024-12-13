#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Animation.h"
#include "Map.h"
#include "SoundManagement.h"
class Bullet
{
private:
	sf::Sprite sprite;
	std::vector<sf::Texture> textures;
	std::vector<sf::Texture> booms;
	Animation animation;
	sf::Sprite explodeSprite;
	Animation boomAnimation;
	bool isExplode;
	sf::Vector2f velocity;
	float gravity;
	sf::Vector2f position;
	float appearTime;
	sf::FloatRect collisionBox;
public:
	// Constructors
	Bullet();

	// Functions
	void Begin(const sf::Vector2f& position);
	void Update(const float& deltaTime, const Map& map);
	void Draw(sf::RenderWindow& window);
	void Reset();

	void handleCollisionWithMap(const float& deltaTime, const Map& map);

	// Collision
	bool mapCollision(const Map& map, sf::Vector2i& collisionAxis);

	// Settes/Getters
	float getAppearTime();
	void setAppearTime(const float& value);
	void setVelocity(const sf::Vector2f& value);
	sf::FloatRect getCollisionBox() const;
};

