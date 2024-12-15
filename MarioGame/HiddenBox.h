#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
class HiddenBox
{
private:
	sf::Sprite sprite;
	std::vector<sf::Texture> textures;
	sf::Texture usedTexture;
	Animation animation;
	sf::Vector2f position;
	sf::FloatRect collisionBox;
	bool used;
public:
	// Constructors
	HiddenBox();

	// Functions
	void Begin(const sf::Vector2f& position);
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	// Setters/Getters
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getPosition() const;
	bool getUsedStatus() const;
	void setUsedStatus(const bool& value);
};

