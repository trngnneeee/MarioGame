#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Renderer.h"
#include "Game.h"
class Map
{
private:
	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture texture;
	
public:
	// Attribute
	float cellSize;
	Map(float cellSize = 32.0f);
	std::vector<std::vector<int>> grid;

	// Functions
	void Begin();
	sf::Vector2f CreateFromImage(const sf::Image& image); // return the spawn position of Mario
	void Draw(sf::RenderWindow& window);
};

