#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "FloatingScore.h"
#include "Animation.h"

class Map
{
private:
	// Cellsize
	float cellSize;
	std::vector<std::vector<int>> grid;

	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture stoneTexture, brickTexture, copperTexture, useBlock, stickTexture, circleTexture;
	sf::Texture fireTextures[3];

	// Hidden box
	sf::Sprite hiddenBoxSprite;
	sf::Texture hiddenBoxTexture[4];
	Animation hiddenBoxAnimation;

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
	void CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& goombasPosition, std::vector<sf::Vector2f>& koopaPosition, sf::Vector2f& winPosition);
	void handleBrickCollision(sf::Vector2f brickPosition);
	void handleHiddenBoxCollision(sf::Vector2f hiddenBoxPosition);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	const std::vector<std::vector<sf::FloatRect>>& getCollisionBoxList() const;
	float getCellSize();
	const std::vector<std::vector<int>>& getGrid() const;
};

