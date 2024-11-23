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
	image.loadFromFile("map1.png");

	// Update texture
	stoneTexture.loadFromFile("./resources/textures/stone.png");
	brickTexture.loadFromFile("./resources/textures/brick.png");
	hiddenBox.loadFromFile("./resources/textures/hiddenbox.png");
	copperTexture.loadFromFile("./resources/textures/copper.png");
	noneTexture.loadFromFile("./resources/textures/block.png");
	coinTextures.clear();
	for (int i = 1; i <= 14; ++i) {
		sf::Texture coinTexture;
		coinTexture.loadFromFile("./resources/textures/coin" + std::to_string(i) + ".png");
		coinTextures.push_back(coinTexture);
	}
}

void Map::CreateFromImage(sf::Vector2f& marioPosition, std::vector<sf::Vector2f>& enemiesPosition) {
	// Clear existing map
	grid.clear();
	coins.clear();
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));

	// Initialize map from image
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			sf::Color color = image.getPixel(i, j);
			if (color == sf::Color::Black) {
				grid[i][j] = 1;
			}
			else if (color == sf::Color::Blue) {
				grid[i][j] = 2;
			}
			else if (color == sf::Color::Yellow) {
				grid[i][j] = 3;
			}
			else if (color == sf::Color::Cyan) {
				grid[i][j] = 4;
			}
			else if (color == sf::Color::Magenta) {
				enemiesPosition.push_back(sf::Vector2f(cellSize * i, cellSize * j));
			}
			else if (color == sf::Color::Red) {
				marioPosition = sf::Vector2f(cellSize * i + cellSize / 2.0f, cellSize * j + cellSize / 2.0f);
			}
			else if (color == sf::Color::Green) { // Cyan indicates a coin
				coins.emplace_back(cellSize * i, cellSize * j, coinTextures, cellSize);
			}
		}
	}

	// Initialize collision boxes
	collisionBoxList.clear();
	for (size_t row = 0; row < grid.size(); row++) {
		std::vector<sf::FloatRect> tmpArr;
		for (size_t col = 0; col < grid[row].size(); col++) {
			if (grid[row][col] != 0) {
				sf::FloatRect tmp(cellSize * row, cellSize * col, cellSize, cellSize);
				tmpArr.push_back(tmp);
			}
			else {
				tmpArr.push_back(sf::FloatRect(0, 0, 0, 0));
			}
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

void Map::Update(float deltaTime, const sf::FloatRect& marioCollisionBox, int& marioPoints, int& marioCoins) {
	// C?p nh?t các ?i?m n?i
	for (size_t i = 0; i < score.size();) {
		if (score[i]) {
			score[i]->Update(deltaTime);
			if (score[i]->isTimeout()) {
				delete score[i];  // Xóa ?i?m n?i khi h?t th?i gian
				score.erase(score.begin() + i);
				continue;
			}
		}
		i++;
	}

	// Ki?m tra và thu th?p ??ng xu
	for (Coin& coin : coins) {
		if (coin.checkCollision(marioCollisionBox) && !coin.isCollected()) {
			coin.collect(*this);  // Thu th?p ??ng xu và thêm ?i?m vào Map
			marioPoints += 100;    // C?ng ?i?m cho Mario
			marioCoins += 1;
		}
	}
}

void Map::Draw(sf::RenderWindow& window) {
	// V? các kh?i
	for (size_t x = 0; x < grid.size(); x++) {
		for (size_t y = 0; y < grid[x].size(); y++) {
			sf::Texture* texture = nullptr;

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
				texture = &noneTexture;
				break;
			default:
				continue;
			}

			sprite.setTexture(*texture);
			sprite.setPosition(cellSize * x, cellSize * y);
			sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
			window.draw(sprite);
		}
	}

	// V? ??ng xu
	for (Coin& coin : coins) {
		coin.Draw(window);
	}

	// V? các ?i?m n?i
	for (FloatingScore* fs : score) {
		if (fs) {
			fs->Draw(window);
		}
	}
}


void Map::Reset() {
	grid.clear();
	collisionBoxList.clear();
	for (int i = 0; i < score.size(); i++) {
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
const std::vector<Coin>& Map::getCoins() const
{
	return coins;
}
void Map::addFloatingScore(int points, sf::Vector2f position) {
	FloatingScore* newScore = new FloatingScore(points, position);
	score.push_back(newScore);  // Thêm ?i?m vào danh sách score
}