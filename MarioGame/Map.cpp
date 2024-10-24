#include "Map.h"

// Constructor
Map::Map(float cellSize)
	:cellSize(cellSize), grid()
{
}

// Functions
bool Map::checkCollision(double x, double y)
{
	int gridX = static_cast<int>(x / cellSize); // Convert world x to grid
	int gridY = static_cast<int>(y / cellSize); // Convert world y to grid

	// Check bounds
	if (gridX < 0 || gridX >= grid.size() || gridY < 0 || gridY >= grid[gridX].size())
	{
		return false; // Out of bounds, no collision
	}

	return grid[gridX][gridY] == 1; // Check for collision with solid block
}

sf::Vector2f Map::CreateFromImage(const sf::Image& image)
{
	// Clear the previous map (vector)
	grid.clear();

	// Declare new vector
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0)); // Declare new vector with size of the map, all element set to 0
	sf::Vector2f marioPosition;

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

bool flag = 0;

void Map::Draw(Renderer& renderer)
{
	sf::Texture brickTexture;
	if (!brickTexture.loadFromFile("./resources/textures/brick.png"))
		return;

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			if (grid[x][y])
			{
				renderer.Draw(brickTexture, sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
		}
	}
}


