#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "FloatingScore.h"
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
	sf::Texture stoneTexture, brickTexture, copperTexture, useBlock, stickTexture, circleTexture;

	// Fire
	std::vector< sf::Texture> fireTextures;

	// Hidden box
	sf::Sprite hiddenBoxSprite;
	std::vector< sf::Texture> hiddenBoxTexture;
	Animation hiddenBoxAnimation;

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

	// Image
	sf::Image image;

	// Collision box
	std::vector<std::vector<sf::FloatRect>> collisionBoxList;

	// Score
	std::vector<FloatingScore*> score;
public:
	// Constructors
	Map(float cellSize = 32.0f);

	// Functions
	void Begin(const std::string& mapName);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	void CreateFromImage(
		sf::Vector2f& marioPosition, 
		sf::Vector2f& winPosition, 
		std::vector<sf::Vector2f>& goombasPosition, 
		std::vector<sf::Vector2f>& koopaPosition, 
		std::vector<sf::Vector2f>& coinPosition,
		std::vector<sf::Vector2f>& chompersPosition
	);
	void CreateCollisionBox();
	void handleBrickCollision(sf::Vector2f brickPosition);
	void handleHiddenBoxCollision(sf::Vector2f hiddenBoxPosition);

	// Setter/Getter
	const std::vector<std::vector<sf::FloatRect>>& getCollisionBoxList() const;
	float getCellSize();
	const std::vector<std::vector<int>>& getGrid() const;
};

