#pragma once
#include <SFML/Graphics.hpp>
class FloatingScore
{
private:
	sf::Vector2f position;
	float timer;
	int points;
	sf::Text text;
	sf::Font font;
public:
	// Constructors
	FloatingScore(const int& points, sf::Vector2f startPosition);
	// Functions
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);
	bool isTimeout();
};

