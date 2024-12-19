#pragma once
#include <SFML/Graphics.hpp>
class FlyingBridge
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float maxRangeX;
	float minRangeX;
	float maxRangeY;
	float minRangeY;
	sf::FloatRect collisionBox;
public:	
	// Constructors
	FlyingBridge(const sf::Vector2f& velocity, const float& maxRangeX, const float& minRangeX, const float& maxRangeY, const float& minRangeY);

	// Functions
	void Begin(const sf::Vector2f& position);
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);

	// Setters/Getters
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getVelocity() const;
};

