#include "Map.h"

// Constructor
Map::Map(float cellSize)
	:cellSize(cellSize), grid()
{
}

// Functions
void Map::Begin() {
	// Update texture
	/*if (!texture.loadFromFile("./resources/textures/brick.png"))
		return;
	sprite.setTexture(texture);*/

	brickTexture.loadFromFile("./resources/textures/brick.png");
	blockTexture.loadFromFile("./resources/textures/block.png");
	hiddenBox.loadFromFile("./resources/textures/hiddenbox.png");
	copperTexture.loadFromFile("./resources/textures/copper.png");
}

sf::Vector2f Map::CreateFromImage(const sf::Image& image)
{
	// Clear the previous map (vector)
	grid.clear();

	// Declare new vector
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0)); // Declare new vector with size of the map, all element set to 0
	sf::Vector2f marioPosition{};

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
			else if (color == sf::Color::Red)
			{
				marioPosition = sf::Vector2f(cellSize * i + cellSize / 2.0f, cellSize * j + cellSize / 2.0f);
			}
		}
	}
	return marioPosition;
}

void Map::Update()
{	 
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

void Map::Draw(sf::RenderWindow& window){
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			if (grid[x][y] == 1)
			{
				sprite.setTexture(brickTexture);
				sprite.setOrigin(brickTexture.getSize().x / 2.0f, brickTexture.getSize().y);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / brickTexture.getSize().x, cellSize / brickTexture.getSize().x);
				window.draw(sprite);
			}
			else if (grid[x][y] == 2)
			{
				sprite.setTexture(copperTexture);
				sprite.setOrigin(copperTexture.getSize().x / 2.0f, copperTexture.getSize().y);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / copperTexture.getSize().x, cellSize / copperTexture.getSize().x);
				window.draw(sprite);
			}
			else if (grid[x][y] == 3)
			{
				sprite.setTexture(hiddenBox);
				sprite.setOrigin(hiddenBox.getSize().x / 2.0f, hiddenBox.getSize().y);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / hiddenBox.getSize().x, cellSize / hiddenBox.getSize().x);
				window.draw(sprite);
			}
			else if (grid[x][y] == 4)
			{
				sprite.setTexture(blockTexture);
				sprite.setOrigin(blockTexture.getSize().x / 2.0f, blockTexture.getSize().y);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / blockTexture.getSize().x, cellSize / blockTexture.getSize().x);
				window.draw(sprite);
			}
		}
	}
}


