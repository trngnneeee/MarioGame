#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "FloatingScore.h"
#include "FloatingCoin.h"
#include "Animation.h"
#include "SoundManagement.h"

class Map
{
private:
	// Cellsize
	float cellSize;
	std::vector<std::vector<int>> grid;

	// Sprite, Texture
	sf::Sprite sprite;
	sf::Texture stoneTexture, copperTexture, useBlock, stickTexture, circleTexture;

	// Fire
	std::vector< sf::Texture> fireTextures;

	// Castle
	std::vector<sf::Texture> castleTexture;

	// Tube
	sf::Sprite tubeSprite;
	std::vector<sf::Texture> tubeTexture;

	// Collumn + Floor in Map 3
	std::vector<sf::Texture> collumnTexture;

	// Bush
	std::vector<sf::Texture> bigBushTextures;
	std::vector<sf::Texture> triBushTextures;

	// Cloud
	std::vector<sf::Texture> cloudTextures;

	// Water map
	sf::Texture greenBlockTexture, coralTexture, waterTexture;
	std::vector<sf::Texture> blueTubeTextures;

	// Image
	sf::Image image;

	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;

	// Score
	std::vector<FloatingScore*> score;
public:
	// Constructors
	Map(float cellSize = 32.0f);

	///	MAIN FUNCTIONS
	void Begin(const std::string& mapName);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	/// HELPER FUNCTIONS
	// Begin Functions
	void TileBegin();
	void FireBegin();
	void TubeBegin();
	void CastleBegin();
	void CollumnFloorBegin();
	void bigBushBegin();
	void cloudBegin();
	void triBushBegin();
	void blueTubeBegin();
	void CreateFromImage(
		sf::Vector2f& marioPosition, 
		sf::Vector2f& winPosition, 
		sf::Vector2f& endWinPosition,
		std::vector<sf::Vector2f>& goombasPosition, 
		std::vector<sf::Vector2f>& koopaPosition, 
		std::vector<sf::Vector2f>& coinPosition,
		std::vector<sf::Vector2f>& chompersPosition,
		std::vector<sf::Vector2f>& bridgesPosition,
		std::vector<sf::Vector2f>& hiddenBoxesPosition,
		std::vector<sf::Vector2f>& bricksPosition
	);
	void CreateCollisionBox();
	// Update Functions
	void FloatingScoreUpdate(const float& deltaTime);
	// Collision Hanlde Functions
	void handleBrickCollision(sf::Vector2f brickPosition);
	// Draw Functions
	void TileDraw(sf::RenderWindow& window);
	void FloatingScoreDraw(sf::RenderWindow& window);

	// Setter/Getter
	const std::vector<std::vector<sf::FloatRect>>& getCollisionBoxList() const;
	float getCellSize() const;
	const std::vector<std::vector<int>>& getGrid() const;
};

