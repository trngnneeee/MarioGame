#include "Map.h"
#include "EnityColor.h"

// Constructor
Map::Map(float cellSize)
	: cellSize(cellSize), hiddenBoxAnimation(1.5f)
{
}
// Functions
void Map::Begin(const std::string& mapName) {
	// Load map
	image.loadFromFile(mapName);

	// Update texture
	stoneTexture.loadFromFile("./resources/textures/stone.png");
	brickTexture.loadFromFile("./resources/textures/brick.png");
	copperTexture.loadFromFile("./resources/textures/copper.png");
	useBlock.loadFromFile("./resources/textures/block.png");
	stickTexture.loadFromFile("./resources/textures/stick.png");
	circleTexture.loadFromFile("./resources/textures/circle.png");

	// Fire texture
	for (int i = 0; i < 3; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/fire" + std::to_string(i + 1) + ".png");
		fireTextures.push_back(tmp);
	}

	// Hidden box texture
	for (int i = 0; i < 3; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/HiddenBox/hiddenbox" + std::to_string(i + 1) + ".png");
		hiddenBoxTexture.push_back(tmp);
	}
	// Hidden box animation
	for (int i = 0; i < hiddenBoxTexture.size(); i++)
	{
		hiddenBoxAnimation.addFrame(Frame(&hiddenBoxTexture[i], 0.5f * (i + 1)));
	}

	// Tube texture
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/tube" + std::to_string(i + 1) + ".png");
		tubeTexture.push_back(tmp);
	}

	// Castle texture;
	const std::vector<std::string> castleFiles = {
		"castleBrick.png", "castleDoorTop.png", "castleDoorBottom.png",
		"castleTop.png", "castleTopFill.png", "castleWindowLeft.png", "castleWindowRight.png" };
	for (const auto& file : castleFiles) {
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Castle/" + file);
		castleTexture.push_back(tmp);
	}

	// Collumn & Floor
	const std::vector<std::string> collumnFiles = {
		"collumn.png", "floor-mid.png", "floor-left.png",
		"floor-right.png" 
	};
	for (const auto& file : collumnFiles) {
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/" + file);
		collumnTexture.push_back(tmp);
	}

	// Big Bush
	const std::vector<std::string> bigBushFiles = {
		"bigBush-left.png", "bigBush-mid.png", "bigBush-right.png" };
	for (const auto& file : bigBushFiles) {
		sf::Texture tmp;
		tmp.loadFromFile("./resources/backgroundComponent/" + file);
		bigBushTextures.push_back(tmp);
	}
	// Cloud
	const std::vector<std::string> cloudFiles = {
		"cloud-bottom-left.png", "cloud-bottom-mid.png", "cloud-bottom-right.png",
		"cloud-top-left.png", "cloud-top-mid.png", "cloud-top-right.png" };
	for (const auto& file : cloudFiles) {
		sf::Texture tmp;
		tmp.loadFromFile("./resources/backgroundComponent/" + file);
		cloudTextures.push_back(tmp);
	}
	// Tribush
	const std::vector<std::string> triBushFiles = {
		"triBush-additional.png", "triBush-left.png", "triBush-mid.png",
		"triBush-right.png", "triBush-top.png" };
	for (const auto& file : triBushFiles) {
		sf::Texture tmp;
		tmp.loadFromFile("./resources/backgroundComponent/" + file);
		triBushTextures.push_back(tmp);
	}
}

void Map::CreateFromImage(
	sf::Vector2f& marioPosition,
	sf::Vector2f& winPosition,
	std::vector<sf::Vector2f>& goombasPosition,
	std::vector<sf::Vector2f>& koopaPosition,
	std::vector<sf::Vector2f>& coinPosition
)
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
			case EntityType::Circle:
			{
				grid[i][j] = 6;
				winPosition = sf::Vector2f(cellSize * i, cellSize * j);
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
			case EntityType::Coin:
			{
				coinPosition.push_back(sf::Vector2f(cellSize * i, cellSize * j));
				break;
			}
			case EntityType::Tube1:
			{
				grid[i][j] = 11;
				break;
			}
			case EntityType::Tube2:
			{
				grid[i][j] = 12;
				break;
			}
			case EntityType::Tube3:
			{
				grid[i][j] = 13;
				break;
			}
			case EntityType::Tube4:
			{
				grid[i][j] = 14;
				break;
			}
			// Castle
			case EntityType::CastleBrick:
			{
				grid[i][j] = 16;
				break;
			}
			case EntityType::CastleDoorTop:
			{
				grid[i][j] = 17;
				break;
			}
			case EntityType::CastleDoorBottom:
			{
				grid[i][j] = 18;
				break;
			}
			case EntityType::CastleTop:
			{
				grid[i][j] = 19;
				break;
			}
			case EntityType::CastleTopFill:
			{
				grid[i][j] = 20;
				break;
			}
			case EntityType::CastleWindowLeft:
			{
				grid[i][j] = 21;
				break;
			}
			case EntityType::CastleWindowRight:
			{
				grid[i][j] = 22;
				break;
			}
			// Collumn & Floor
			case EntityType::Collumn:
			{
				grid[i][j] = 23;
				break;
			}
			case EntityType::Floor:
			{
				grid[i][j] = 24;
				break;
			}
			case EntityType::FloorRight:
			{
				grid[i][j] = 25;
				break;
			}
			case EntityType::FloorLeft:
			{
				grid[i][j] = 26;
				break;
			}
			// Big Bush
			case EntityType::bigBushLeft:
			{
				grid[i][j] = 27;
				break;
			}
			case EntityType::bigBushMid:
			{
				grid[i][j] = 28;
				break;
			}
			case EntityType::bigBushRight:
			{
				grid[i][j] = 29;
				break;
			}
			//Cloud
			case EntityType::cloudBottomLeft:
			{
				grid[i][j] = 30;
				break;
			}
			case EntityType::cloudBottomMid:
			{
				grid[i][j] = 31;
				break;
			}
			case EntityType::cloudBottomRight:
			{
				grid[i][j] = 32;
				break;
			}
			case EntityType::cloudTopLeft:
			{
				grid[i][j] = 33;
				break;
			}
			case EntityType::cloudTopMid:
			{
				grid[i][j] = 34;
				break;
			}
			case EntityType::cloudTopRight:
			{
				grid[i][j] = 35;
				break;
			}
			//triBush
			case EntityType::triBushAdditional:
			{
				grid[i][j] = 36;
				break;
			}
			case EntityType::triBushLeft:
			{
				grid[i][j] = 37;
				break;
			}
			case EntityType::triBushMid:
			{
				grid[i][j] = 38;
				break;
			}
			case EntityType::triBushRight:
			{
				grid[i][j] = 39;
				break;
			}
			case EntityType::triBushTop:
			{
				grid[i][j] = 40;
				break;
			}
			}
		}
	}
}

void Map::CreateCollisionBox()
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

void Map::handleBrickCollision(sf::Vector2f brickPosition)
{
	int x = static_cast<int>(brickPosition.x / cellSize);
	int y = static_cast<int>(brickPosition.y / cellSize);

	grid[x][y] = 0;
	collisionBoxList[x][y] = sf::FloatRect(0, 0, 0, 0);

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

	hiddenBoxSprite.setTexture(*hiddenBoxAnimation.update(deltaTime));
}

void Map::Draw(sf::RenderWindow& window) {
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
			case 4: 
				hiddenBoxSprite.setPosition(cellSize * x, cellSize * y);
				hiddenBoxSprite.setScale(cellSize / hiddenBoxTexture[0].getSize().x, cellSize / hiddenBoxTexture[0].getSize().y);
				window.draw(hiddenBoxSprite);
				break;
			case 3:
				texture = &brickTexture;
				break;
			case 5:
				texture = &useBlock;
				break;
			// Win Milestone
			case 6:
			{
				texture = &circleTexture;
				break;
			}
			case 7:
			{
				texture = &stickTexture;
				break;
			}
			// Fire
			case 8:
			{
				texture = &fireTextures[0];
				break;
			}
			case 9:
			{
				texture = &fireTextures[1];
				break;
			}
			case 10:
			{
				texture = &fireTextures[2];
				break;
			}
			// Tube
			case 11:
			{
				texture = &tubeTexture[0];
				break;
			}
			case 12:
			{
				texture = &tubeTexture[1];
				break;
			}
			case 13:
			{
				texture = &tubeTexture[2];
				break;
			}
			case 14:
			{
				texture = &tubeTexture[3];
				break;
			}
			// Castle
			case 16:
			{
				texture = &castleTexture[0];
				break;
			}
			case 17:
			{
				texture = &castleTexture[1];
				break;
			}
			case 18:
			{
				texture = &castleTexture[2];
				break;
			}
			case 19:
			{
				texture = &castleTexture[3];
				break;
			}
			case 20:
			{
				texture = &castleTexture[4];
				break;
			}
			case 21:
			{
				texture = &castleTexture[5];
				break;
			}
			case 22:
			{
				texture = &castleTexture[6];
				break;
			}
			// Collum + Floor
			case 23:
			{
				texture = &collumnTexture[0];
				break;
			}
			case 24:
			{
				texture = &collumnTexture[1];
				break;
			}
			case 25:
			{
				texture = &collumnTexture[2];
				break;
			}
			case 26:
			{
				texture = &collumnTexture[3];
				break;
			}
			// Big Bush
			case 27:
			{
				texture = &bigBushTextures[0];
				break;
			}
			case 28:
			{
				texture = &bigBushTextures[1];
				break;
			}
			case 29:
			{
				texture = &bigBushTextures[2];
				break;
			}
			// Cloud
			case 30:
			{
				texture = &cloudTextures[0];
				break;
			}
			case 31:
			{
				texture = &cloudTextures[1];
				break;
			}
			case 32:
			{
				texture = &cloudTextures[2];
				break;
			}
			case 33:
			{
				texture = &cloudTextures[3];
				break;
			}
			case 34:
			{
				texture = &cloudTextures[4];
				break;
			}
			case 35:
			{
				texture = &cloudTextures[5];
				break;
			}
			// triBush
			case 36:
			{
				texture = &triBushTextures[0];
				break;
			}
			case 37:
			{
				texture = &triBushTextures[1];
				break;
			}
			case 38:
			{
				texture = &triBushTextures[2];
				break;
			}
			case 39:
			{
				texture = &triBushTextures[3];
				break;
			}
			case 40:
			{
				texture = &triBushTextures[4];
				break;
			}
			default:
				continue;
			}
			if (texture)
			{
				sprite.setTexture(*texture);
				sprite.setPosition(cellSize* x, cellSize* y);
				sprite.setScale(cellSize / texture->getSize().x, cellSize / texture->getSize().x);
				window.draw(sprite);
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
	for (int i = 0; i < grid.size(); i++)
	{
		grid[i].clear();
		collisionBoxList[i].clear();
	}
	grid.clear();
	collisionBoxList.clear();
	for (int i = 0; i < score.size(); i++)
	{
		delete score[i];
	}
	score.clear();
	hiddenBoxAnimation.Reset();
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
