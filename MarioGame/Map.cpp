#include "Map.h"
#include "EnityColor.h"

// Constructor
Map::Map(float cellSize)
	: cellSize(cellSize), hiddenBoxAnimation(6.0f)
{
}
// Functions
void Map::Begin() {
	// Load map
	image.loadFromFile("map2newnewFixed.png");

	// Update texture
	stoneTexture.loadFromFile("./resources/textures/stone.png");
	brickTexture.loadFromFile("./resources/textures/brick.png");
	copperTexture.loadFromFile("./resources/textures/copper.png");
	useBlock.loadFromFile("./resources/textures/block.png");
	stickTexture.loadFromFile("./resources/textures/stick.png");
	circleTexture.loadFromFile("./resources/textures/circle.png");

	fireTextures[0].loadFromFile("./resources/textures/fire1.png");
	fireTextures[1].loadFromFile("./resources/textures/fire2.png");
	fireTextures[2].loadFromFile("./resources/textures/fire3.png");

	hiddenBoxTexture[0].loadFromFile("./resources/textures/hiddenbox1.png");
	hiddenBoxTexture[1].loadFromFile("./resources/textures/hiddenbox2.png");
	hiddenBoxTexture[2].loadFromFile("./resources/textures/hiddenbox3.png");
	hiddenBoxTexture[3].loadFromFile("./resources/textures/hiddenbox4.png");

	hiddenBoxAnimation.addFrame(Frame(&hiddenBoxTexture[0], 1.5f));
	hiddenBoxAnimation.addFrame(Frame(&hiddenBoxTexture[1], 3.0f));
	hiddenBoxAnimation.addFrame(Frame(&hiddenBoxTexture[2], 4.5f));
	hiddenBoxAnimation.addFrame(Frame(&hiddenBoxTexture[3], 6.0f));
}

void Map::CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& goombasPosition, std::vector<sf::Vector2f>& koopaPosition, sf::Vector2f& winPosition)
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
			case EntityType::Win:
			{
				winPosition = sf::Vector2f(cellSize * i , cellSize * j);
				break;
			}
			case EntityType::Circle:
			{
				grid[i][j] = 6;
				break;
			}
			case EntityType::Stick:
			{
				grid[i][j] = 7;
				break;
			}
			case EntityType::Fire1:
			{
				grid[i][j] = 8;
				break;
			}
			case EntityType::Fire2:
			{
				grid[i][j] = 9;
				break;
			}
			case EntityType::Fire3:
			{
				grid[i][j] = 10;
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

void Map::handleBrickCollision(sf::Vector2f brickPosition)
{
	int x = static_cast<int>(brickPosition.x / cellSize);
	int y = static_cast<int>(brickPosition.y / cellSize);

	grid[x][y] = 0;

	FloatingScore* newScore = new FloatingScore(50, brickPosition);
	score.push_back(newScore);
}

void Map::handleHiddenBoxCollision(sf::Vector2f hiddenBoxPosition)
{
	int x = static_cast<int>(hiddenBoxPosition.x / cellSize);
	int y = static_cast<int>(hiddenBoxPosition.y / cellSize);

	grid[x][y] = 5;
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

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 4)
			{
				hiddenBoxSprite.setTexture(*hiddenBoxAnimation.update(deltaTime));
			}
		}
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
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			case 2:
				texture = &copperTexture;
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			case 3:
				texture = &brickTexture;
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			case 4:
				hiddenBoxSprite.setPosition(cellSize * x, cellSize * y);
				hiddenBoxSprite.setScale(cellSize / hiddenBoxTexture[0].getSize().x, cellSize / hiddenBoxTexture[0].getSize().y);
				window.draw(hiddenBoxSprite);
				break;
			case 5:
				texture = &useBlock;
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			case 6:
			{
				texture = &circleTexture;
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			}
			case 7:
			{
				texture = &stickTexture;
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			}
			case 8:
			{
				texture = &fireTextures[0];
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			}
			case 9:
			{
				texture = &fireTextures[1];
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			}
			case 10:
			{
				texture = &fireTextures[2];
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize * x, cellSize * y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
				break;
			}
			default:
				continue;
			}
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
