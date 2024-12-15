#pragma once
#include "SoundManagement.h"
#include "MapTransition.h"
#include "Map.h"
#include "Mario.h"
#include "EnemyFactory.h"
#include "Goombas.h"
#include "Koopa.h"
#include "Chomper.h"
#include "Coin.h"
#include "Background.h"
#include "GameTime.h"
#include "Menu.h"
#include "LoginMenu.h"
#include "UICounter.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include "FireFlower.h"
#include "GameState.h"
#include <vector>
#include <iostream>
#include <string>
#include "PauseMenu.h"
#include "FlyingBridge.h"
#include "Flag.h"
class MarioGame
{
private:
	MapTransition mapTransition;
	Map map;
	Mario mario;
	std::vector<Goombas*> goombas;
	std::vector<Koopa*> koopas;
	std::vector<Chomper*> chompers;
	std::vector<std::unique_ptr<Coin>> coins;
	Background background;
	GameTime gameTime;
	UICounter UI;
	Menu menu;
	LoginMenu loginMenu;
	Camera camera;
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
	void Begin(sf::RenderWindow& window);
	void Update(const float& deltaTime, GameState& gameState, sf::RenderWindow& window);
	void Render(sf::RenderWindow& window, GameState& gameState);

	/// HELPER FUNCTIONS
	// BEGIN FUNCTIONS
	void MusicBegin();
	void HandleStart(GameState& gameState, sf::RenderWindow& window);
	void MapTransitionBegin();
	void MapBegin(
		sf::Vector2f& marioPosition, 
		sf::Vector2f& winPosition, 
		std::vector<sf::Vector2f>& goombasPosition,
		std::vector<sf::Vector2f>& koopasPosition, 
		std::vector<sf::Vector2f>& coinsPosition,
		std::vector<sf::Vector2f>& chompersPosition,
		std::vector<sf::Vector2f>& bridgesPosition
	);
	void MarioBegin(const sf::Vector2f& marioPosition);
	void EnemyBegin(const std::vector<sf::Vector2f>& goombasPosition, const std::vector<sf::Vector2f>& koopasPosition);
	void ChomperBegin(const std::vector<sf::Vector2f>& chompersPosition);
	void FlyingBridgeBegin(const std::vector<sf::Vector2f>& bridgesPosition);
	void CoinBegin(const std::vector<sf::Vector2f>& coinsPosition);
	void BackgroundBegin();
	void GameTimeBegin();
	void UICounterBegin();
	void CameraBegin();
	void MenuBegin(sf::RenderWindow& window);
	void LoginMenuBegin(sf::RenderWindow& window);
	void FlagBegin(sf::Vector2f winPosition);

	// UPDATE FUNCTIONS
	void MusicUpdate();
	bool MapTransitionUpdate(const float& deltaTime);
	void MapUpdate(const float& deltaTime);
	void MarioUpdate(
		const float& deltaTime,
		Map& map,
		GameState& gameState
	);
	void GoombaUpdate(const float& deltaTime, const Map& map);
	void KoopaUpdate(const float& deltaTime, const Map& map);
	void ChomperUpdate(const float& deltaTime);
	void FlyingBridgeUpdate(const float& deltaTime);
	void CoinUpdate(const float& deltaTime);
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

	/*CAUTIOUS: KEEP THIS DRAW ORDER FOR CORRECT Z-INDEX*/
	void BackgroundDraw(sf::RenderWindow& window);
	void HiddenBoxItemDraw(sf::RenderWindow& window);
	void ChomperDraw(sf::RenderWindow& window);
	void MapDraw(sf::RenderWindow& window);
	void FlyingBridgeDraw(sf::RenderWindow& window);
	void FlagDraw(sf::RenderWindow& window);
	void MarioDraw(sf::RenderWindow& window);
	void EnemyDraw(sf::RenderWindow& window);
	void CoinDraw(sf::RenderWindow& window);
	void UIDraw(sf::RenderWindow& window);

	// RESET FUNCTIONS
	void GameReset();
};

