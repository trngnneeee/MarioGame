#pragma once
#include "SoundManagement.h"
#include "MapTransition.h"
#include "Map.h"
#include "Mario.h"
#include "EnemyFactory.h"
#include "Goombas.h"
#include "Koopa.h"
#include "Chomper.h"
#include "Bird.h"
#include "Coin.h"
#include "Background.h"
#include "GameTime.h"
#include "Menu.h"
#include "LoginMenu.h"
#include "UICounter.h"
#include "Brick.h"
#include "BrickParticle.h"
#include "FloatingScore.h"
#include "FloatingCoin.h"
#include "HiddenBox.h"
#include "HiddenBoxItemFactory.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include "FireFlower.h"
#include "GameState.h"
#include "PauseMenu.h"
#include "FlyingBridge.h"
#include "Flag.h"
#include "GameOver.h"
#include <vector>
#include <iostream>
#include <string>
class MarioGame
{
private:
	MapTransition mapTransition;
	Map map;
	Mario mario;
	std::vector<Goombas*> goombas;
	std::vector<Koopa*> koopas;
	std::vector<Chomper*> chompers;
	std::vector<Bird*> birds;
	std::vector<std::unique_ptr<Coin>> coins;
	Background background;
	GameTime gameTime;
	UICounter UI;

	Menu menu;
	LoginMenu loginMenu;
	GameOver gameOver;

	Camera camera;
	std::vector<Brick*> bricks;
	std::vector<BrickParticle*> brickParticles;
	std::vector<FloatingCoin*> floatingCoin;
	std::vector<FloatingScore*> floatingScore;
	std::vector<HiddenBox*> hiddenBoxes;
	std::vector<PowerUpMushroom*> mushrooms;
	std::vector<InvicibleStar*> stars;
	std::vector<FireFlower*> flowers;
	sf::Vector2f winPosition;
	sf::Vector2f endWinPosition;
	std::vector<FlyingBridge*> bridges;
	Flag winFlag;

	float updateRange;
	bool pause;
	PauseMenu pauseMenu;
public:
	/// MAIN FUNCTIONS
	void Event(sf::RenderWindow& window, GameState& gameState);
	void Begin(sf::RenderWindow& window, const int& characterSelected, GameState& gameState);
	void Update(const float& deltaTime, GameState& gameState, sf::RenderWindow& window);
	void Render(sf::RenderWindow& window, GameState& gameState);

	/// HELPER FUNCTIONS
	// BEGIN FUNCTIONS
	void MusicBegin();
	void MapTransitionBegin();
	void MapBegin(
		sf::Vector2f& marioPosition, 
		sf::Vector2f& winPosition, 
		std::vector<sf::Vector2f>& goombasPosition,
		std::vector<sf::Vector2f>& koopasPosition, 
		std::vector<sf::Vector2f>& coinsPosition,
		std::vector<sf::Vector2f>& chompersPosition,
		std::vector<sf::Vector2f>& bridgesPosition,
		std::vector<sf::Vector2f>& hiddenBoxesPosition,
		std::vector<sf::Vector2f>& bricksPosition,
		std::vector<sf::Vector2f>& birdsPosition
	);
	void MarioBegin(const sf::Vector2f& marioPosition, const int& characterSelected);
	void EnemyBegin(const std::vector<sf::Vector2f>& goombasPosition, const std::vector<sf::Vector2f>& koopasPosition, const std::vector<sf::Vector2f>& birdsPosition);
	void ChomperBegin(const std::vector<sf::Vector2f>& chompersPosition);
	void FlyingBridgeBegin(const std::vector<sf::Vector2f>& bridgesPosition);
	void CoinBegin(const std::vector<sf::Vector2f>& coinsPosition);
	void BrickBegin(const std::vector<sf::Vector2f>& bricksPosition);
	void HiddenBoxBegin(const std::vector<sf::Vector2f>& hiddenBoxesPosition);
	void BackgroundBegin();
	void GameTimeBegin();
	void UICounterBegin();
	void CameraBegin();
	void MenuBegin(sf::RenderWindow& window);
	void LoginMenuBegin(sf::RenderWindow& window);
	void GameOverBegin();
	void FlagBegin(sf::Vector2f winPosition);

	// UPDATE FUNCTIONS
	void MusicUpdate();
	bool MapTransitionUpdate(const float& deltaTime);
	void GameOverUpdate(const float& deltaTime);
	void MapUpdate(const float& deltaTime);
	void MarioUpdate(
		const float& deltaTime,
		Map& map,
		GameState& gameState
	);
	void GoombaUpdate(const float& deltaTime, const Map& map);
	void KoopaUpdate(const float& deltaTime, const Map& map);
	void ChomperUpdate(const float& deltaTime);
	void BirdUpdate(const float& deltaTime);
	void FlyingBridgeUpdate(const float& deltaTime);
	void CoinUpdate(const float& deltaTime);
	void BrickUpdate(const float& deltaTime);
	void BrickParticleUpdate(const float& deltaTime);
	void FloatingScoreUpdate(const float& deltaTime);
	void FloatingCoinUpdate(const float& deltaTime);
	void HiddenBoxUpdate(const float& deltaTime);
	void GameTimeUpdate(const float& deltaTime);
	void UIUpdate(const float& deltaTime);

	void CameraUpdate();
	void MushroomUpdate(const float& deltaTime, const Map& map);
	void StarUpdate(const float& deltaTime, const Map& map);
	void FlowerUpdate(const float& deltaTime, const Map& map);
	void FlagUpdate(const float& deltaTime);

	void DeadUpdate(GameState& gameState);
	bool WinDetect();

	// DRAW FUNCTIONS
	void MapTransitionDraw(sf::RenderWindow& window);
	void MenuDraw(sf::RenderWindow& window);
	void LoginMenuDraw(sf::RenderWindow& window);
	void GameOverDraw(sf::RenderWindow& window);

	/*CAUTIOUS: KEEP THIS DRAW ORDER FOR CORRECT Z-INDEX*/
	void BackgroundDraw(sf::RenderWindow& window);
	void HiddenBoxItemDraw(sf::RenderWindow& window);
	void ChomperDraw(sf::RenderWindow& window);
	void MapDraw(sf::RenderWindow& window);
	void BrickDraw(sf::RenderWindow& window);
	void BrickParticleDraw(sf::RenderWindow& window);
	void FloatingScoreDraw(sf::RenderWindow& window);
	void FloatingCoinDraw(sf::RenderWindow& window);
	void HiddenBoxDraw(sf::RenderWindow& window);
	void FlyingBridgeDraw(sf::RenderWindow& window);
	void FlagDraw(sf::RenderWindow& window);
	void MarioDraw(sf::RenderWindow& window);
	void EnemyDraw(sf::RenderWindow& window);
	void CoinDraw(sf::RenderWindow& window);
	void UIDraw(sf::RenderWindow& window);

	// RESET FUNCTIONS
	void GameReset();
};

