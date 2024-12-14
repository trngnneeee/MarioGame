#pragma once
#include <SFML/Graphics.hpp>
class FlyingBridge
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float maxRange;
	float minRange;
	sf::FloatRect collisionBox;
public:	
	// Constructors
	FlyingBridge();

	// Functions
	void Begin(const sf::Vector2f& position);
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);

	// Setters/Getters
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getVelocity() const;
};

