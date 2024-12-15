#pragma once
#include <SFML/Graphics.hpp>
class Flag
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
public:
	// Functions
	void Begin(const sf::Vector2f& position);
	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow& window);

	// Setter/Getter
	void setPosition(const sf::Vector2f& position);
};	

