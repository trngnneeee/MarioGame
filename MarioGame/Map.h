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

	// Overlay
	sf::RectangleShape overlayRect;
public:
	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;

	// Attribute
	float cellSize;
	Map(float cellSize = 32.0f);
	std::vector<std::vector<int>> grid;

	// Functions
	void Begin();
	void CreateFromImage(const sf::Image& image, sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& enemiesPosition); // return the spawn position of Mario
	void Update();
	void Draw(sf::RenderWindow& window);
	void Reset();
};

