#include "Map.h"
#include "EnityColor.h"
#include <iostream>

// Constructor
Map::Map(float cellSize)
	:cellSize(cellSize), grid()
{
}
// Functions
void Map::Begin() {
	// Load map
	image.loadFromFile("map2.png");

	// Update texture
	stoneTexture.loadFromFile("./resources/textures/stone.png");
	brickTexture.loadFromFile("./resources/textures/brick.png");
	hiddenBox.loadFromFile("./resources/textures/hiddenbox.png");
	copperTexture.loadFromFile("./resources/textures/copper.png");
	useBlock.loadFromFile("./resources/textures/block.png");
}

void Map::CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& goombasPosition, std::vector<sf::Vector2f>& koopaPosition)
{
	// Clear the previous map (vector)
	grid.clear();
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));

	// Init map
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			sf::Color color = image.getPixel(i, j);
			EntityType entityType = getEntityTypeFromColor(color);
			switch (entityType)
			{
			case EntityType::Stone:
			{
				grid[i][j] = 1;
				break;
			}
			case EntityType::Copper:
			{
				grid[i][j] = 2;
				break;
			}
			case EntityType::Brick:
			{
				grid[i][j] = 3;
				break;
			}
			case EntityType::HiddenBox:
			{
				grid[i][j] = 4;
				break;
			}
			case EntityType::useBlock:
			{
				grid[i][j] = 5;
				break;
			}
			case EntityType::Goomba:
			{
				goombasPosition.push_back(sf::Vector2f(cellSize * i, cellSize * j));
				break;
			}
			case EntityType::Koopa:
			{
				koopaPosition.push_back(sf::Vector2f(cellSize * i, cellSize * j));
				break;
			}
			case EntityType::Mario:
			{
				marioPosition = sf::Vector2f(cellSize * i + cellSize / 2.0f, cellSize * j + cellSize / 2.0f);
				break;
			}
			}
		}
	}

	// Init collision box
	for (int row = 0; row < grid.size(); row++)
	{
		std::vector<sf::FloatRect> tmpArr;
		for (int colum = 0; colum < grid[row].size(); colum++)
		{
			if (grid[row][colum] != 0)
			{
				sf::FloatRect tmp(cellSize * row, cellSize * colum, cellSize, cellSize);
				tmpArr.push_back(tmp);
			}
			else tmpArr.push_back(sf::FloatRect(0, 0, 0, 0));
		}
		collisionBoxList.push_back(tmpArr);
	}
}

void Map::handleBrickCollision(sf::Vector2f hiddenBoxPosition)
{
	int x = static_cast<int>(hiddenBoxPosition.x / cellSize);
	int y = static_cast<int>(hiddenBoxPosition.y / cellSize);

	grid[x][y] = 0;

	FloatingScore* newScore = new FloatingScore(50, hiddenBoxPosition);
	score.push_back(newScore);
}

void Map::Update(float deltaTime)
{	
	for (int i = 0; i < score.size();)
	{
		if (score[i])
		{
			score[i]->Update(deltaTime);
			if (score[i]->isTimeout())
			{
				delete score[i];
				score.erase(score.begin() + i);
				continue;
			}
		}
		i++;
	}
}

void Map::Draw(sf::RenderWindow& window){
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			sf::Texture* texture = nullptr;

			// Determine the texture and render block type
			switch (grid[x][y]) {
			case 1:
				texture = &stoneTexture;
				break;
			case 2:
				texture = &copperTexture;
				break;
			case 3:
				texture = &brickTexture;
				break;
			case 4:
				texture = &hiddenBox;
				break;
			case 5:
				texture = &useBlock;
				break;
			default:
				continue;
			}

			// Set and draw the block sprite
			sprite.setTexture(*texture);
			sprite.setPosition(cellSize * x, cellSize * y);
			sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
			window.draw(sprite);
		}
	}
	for (int i = 0; i < score.size(); i++)
	{
		if (score[i])
			score[i]->Draw(window);
	}
}

void Map::Reset()
{
	grid.clear();
	collisionBoxList.clear();
	for (int i = 0; i < score.size(); i++)
	{
		delete score[i];
	}
	score.clear();
}

const std::vector<std::vector<sf::FloatRect>>& Map::getCollisionBoxList() const
{
	return collisionBoxList;
}

float Map::getCellSize()
{
	return cellSize;
}

const std::vector<std::vector<int>>& Map::getGrid() const
{
	return grid;
}
