#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Renderer.h"
#include "Game.h"
class Map
{
private:
	
public:
	// Attribute
	float cellSize;
	Map(float cellSize = 32.0f);
	std::vector<std::vector<int>> grid;

	// Functions
	bool checkCollision(double x, double y);
	sf::Vector2f CreateFromImage(const sf::Image& image); // return the spawn position of Mario
	void Draw(Renderer& renderer);
};

