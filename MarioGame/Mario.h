#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Renderer.h"
#include "Map.h"

class Mario
{
private:
	
public:
	// Position
	sf::Vector2f position{};

	// Texture, Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	// Box collision
	sf::FloatRect collisionBox;

	// Functions
	void Begin();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

