#pragma once
#include <SFML/Graphics.hpp>
class Brick
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::FloatRect collisionBox;
	sf::Vector2f startPosition;
	bool isBouncing;
	float bounceTime;
	float bounceDuration;
	float bounceHeight;
	bool isBreak;
public:
	// Constructors
	Brick();

	// Functions
	void Begin(const sf::Vector2f& position);
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);

	void HandleBounceUp(const float& deltaTime);

	// Setters/Getters
	bool getBounceStatus() const;
	void setBounceStatus(const bool& value);
	bool getBrokeStatus() const;
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getStartPosition() const;
};

