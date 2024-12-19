#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
class BrickParticle
{
private:
	std::vector<sf::Texture> textures;
	sf::Sprite sprite;
	Animation animation;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float timer;
	float duration;
	float gravity;
public:
	// Constructors
	BrickParticle();

	// Functions
	void Begin(const sf::Vector2f& position, const sf::Vector2f& velocity);
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();
	bool isTimeOut();
};

