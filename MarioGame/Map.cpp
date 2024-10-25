#include "Map.h"

// Constructor
Map::Map(float cellSize)
	:cellSize(cellSize), grid()
{
}

// Functions
void Map::Begin() {
	// Update texture
	if (!texture.loadFromFile("./resources/textures/brick.png"))
		return;
	sprite.setTexture(texture);
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
			else if (color == sf::Color::Red)
			{
				marioPosition = sf::Vector2f(cellSize * i + cellSize / 2.0f, cellSize * j + cellSize / 2.0f);
			}
		}
	}
	return marioPosition;
}

void Map::Draw(sf::RenderWindow& window){
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			if (grid[x][y])
			{
				sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
				sprite.setPosition(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				sprite.setScale(cellSize / texture.getSize().x, cellSize / texture.getSize().x);
				window.draw(sprite);
			}
		}
	}
}


