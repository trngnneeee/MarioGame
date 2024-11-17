#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "FloatingScore.h"

class Map
{
private:
	// Cellsize
	float cellSize;
	std::vector<std::vector<int>> grid;

	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture brickTexture, blockTexture, hiddenBox, copperTexture;

	// Image
	sf::Image image;

	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;

	// Score
	std::vector<FloatingScore*> score;
public:
	Map(float cellSize = 32.0f);

	// Functions
	void Begin();
	void CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& enemiesPosition);
	void handleHiddenBoxCollision(sf::Vector2f hiddenBoxPosition);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	const std::vector<std::vector<sf::FloatRect>>& getCollisionBoxList() const;
	float getCellSize();
	const std::vector<std::vector<int>>& getGrid() const;
};

