#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
class Map
{
private:
	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture brickTexture, blockTexture, hiddenBox, copperTexture;

	
public:
	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;

	// Attribute
	float cellSize;
	Map(float cellSize = 32.0f);
	std::vector<std::vector<int>> grid;

	// Functions
	void Begin();
	sf::Vector2f CreateFromImage(const sf::Image& image); // return the spawn position of Mario
	void Update();
	void Draw(sf::RenderWindow& window);
};

