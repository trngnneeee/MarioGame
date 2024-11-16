#include "Map.h"
#include <iostream>

// Constructor
Map::Map(float cellSize)
	:cellSize(cellSize), grid()
{
}
// Functions
void Map::Begin() {
	// Load map
	image.loadFromFile("map3.png");

	// Update texture
	brickTexture.loadFromFile("./resources/textures/brick.png");
	blockTexture.loadFromFile("./resources/textures/block.png");
	hiddenBox.loadFromFile("./resources/textures/hiddenbox.png");
	copperTexture.loadFromFile("./resources/textures/copper.png");
}

void Map::CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& enemiesPosition)
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
			if (color == sf::Color::Black) // if the pixel of the map is Black, means there is a brick -> set it to 1
			{
				grid[i][j] = 1;
			}
			else if (color == sf::Color::Blue)
				grid[i][j] = 2;
			else if (color == sf::Color::Yellow)
				grid[i][j] = 3;
			else if (color == sf::Color::Green)
				grid[i][j] = 4;
			else if (color == sf::Color::Magenta)
			{
				enemiesPosition.push_back(sf::Vector2f(cellSize * i, cellSize * j));
			}
			else if (color == sf::Color::Red)
			{
				marioPosition = sf::Vector2f(cellSize * i + cellSize / 2.0f, cellSize * j + cellSize / 2.0f);
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

void Map::Update(sf::Vector2f hiddenBoxPosition)
{	
	int x = static_cast<int>(hiddenBoxPosition.x / cellSize);
	int y = static_cast<int>(hiddenBoxPosition.y / cellSize);
	
	grid[x][y] = 4;

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
				texture = &brickTexture;
				break;
			case 2:
				texture = &copperTexture;
				break;
			case 3:
				texture = &hiddenBox;
				break;
			case 4:
				texture = &blockTexture;
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
}

void Map::Reset()
{
	grid.clear();
	collisionBoxList.clear();
}
