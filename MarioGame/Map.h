#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "FloatingScore.h"

class Map
{
private:
	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture brickTexture, blockTexture, hiddenBox, copperTexture;

	// Overlay
	sf::RectangleShape overlayRect;

	// Image
	sf::Image image;
public:
	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;

	// Attribute
	float cellSize;
	std::vector<std::vector<int>> grid;
	Map(float cellSize = 32.0f);

	// Functions
	void Begin();
	void CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& enemiesPosition); // return the spawn position of Mario
	void Update(sf::Vector2f hiddenBoxPosition);
	void Draw(sf::RenderWindow& window);
	void Reset();
};

