#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class FloatingCoin
{
private:
	sf::Vector2f position;
	sf::Vector2f startPosition;
	float timer;
	sf::Sprite sprite;
	std::vector<sf::Texture> textures;
	Animation animation;

public:
	// Constructors
	FloatingCoin(sf::Vector2f startPosition);
	// Functions
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);
	bool isTimeOut() const;
	void Reset();
};

