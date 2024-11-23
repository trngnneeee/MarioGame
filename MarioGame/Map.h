#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "Coin.h"
#include "FloatingScore.h"

class Map
{
private:
	// Cellsize
	float cellSize;
	std::vector<std::vector<int>> grid;

	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture stoneTexture, brickTexture, hiddenBox, copperTexture, noneTexture;
	std::vector<sf::Texture> coinTextures;
	// Image
	sf::Image image;

	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;
	// Coins
	std::vector<Coin> coins;
	// Score
	std::vector<FloatingScore*> score;
public:
	Map(float cellSize = 32.0f);

	// Functions
	void Begin();
	void CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& enemiesPosition);
	void handleBrickCollision(sf::Vector2f hiddenBoxPosition);
	void Update(float deltaTime, const sf::FloatRect& marioCollisionBox, int& marioPoints, int& marioCoins);
	void Draw(sf::RenderWindow& window);
	void Reset();

	const std::vector<std::vector<sf::FloatRect>>& getCollisionBoxList() const;
	float getCellSize();
	const std::vector<std::vector<int>>& getGrid() const;
	const std::vector<Coin>& getCoins() const;
	void addFloatingScore(int points, sf::Vector2f position);
};

