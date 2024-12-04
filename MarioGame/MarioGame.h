#pragma once
#include "SoundManagement.h"
#include "MapTransition.h"
#include "Map.h"
#include "Mario.h"
#include "EnemyFactory.h"
#include "Goombas.h"
#include "Koopa.h"
#include "Coin.h"
#include "Background.h"
#include "GameTime.h"
#include "Menu.h"
#include "UICounter.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include "GameState.h"
#include <vector>
#include <iostream>
#include <string>
#include "PauseMenu.h"
class MarioGame
{
private:
	MapTransition mapTransition;
	Map map;
	Mario mario;
	std::vector<Goombas*> goombas;
	std::vector<Koopa*> koopas;
	std::vector<std::unique_ptr<Coin>> coins;
	Background background;
	GameTime gameTime;
	UICounter UI;
	Menu menu;
	Camera camera;
	std::vector<PowerUpMushroom*> mushrooms;
	std::vector<InvicibleStar*> stars;
	sf::Vector2f winPosition;

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
	void MapTransitionBegin();
	void MapBegin(
		sf::Vector2f& marioPosition, 
		sf::Vector2f& winPosition, 
		std::vector<sf::Vector2f>& goombasPosition,
		std::vector<sf::Vector2f>& koopasPosition, 
		std::vector<sf::Vector2f>& coinsPosition
	);
	void MarioBegin(const sf::Vector2f& marioPosition);
	void EnemyBegin(const std::vector<sf::Vector2f>& goombasPosition, const std::vector<sf::Vector2f>& koopasPosition);
	void CoinBegin(const std::vector<sf::Vector2f>& coinsPosition);
	void BackgroundBegin();
	void GameTimeBegin();
	void UICounterBegin();
	void CameraBegin();
	void MenuBegin(sf::RenderWindow& window);

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
	void CoinUpdate(const float& deltaTime);
	void GameTimeUpdate(const float& deltaTime);
	void UIUpdate(const float& deltaTime);

	void CameraUpdate();
	void MushroomUpdate(const float& deltaTime, const Map& map);
	void StarUpdate(const float& deltaTime, const Map& map);
	void DeadUpdate(GameState& gameState);
	bool WinDetect();

	// DRAW FUNCTIONS
	void MapTransitionDraw(sf::RenderWindow& window);
	void MenuDraw(sf::RenderWindow& window);

	/*CAUTIOUS: KEEP THIS DRAW ORDER FOR CORRECT Z-INDEX*/
	void BackgroundDraw(sf::RenderWindow& window);
	void HiddenBoxItemDraw(sf::RenderWindow& window);
	void MapDraw(sf::RenderWindow& window);
	void MarioDraw(sf::RenderWindow& window);
	void EnemyDraw(sf::RenderWindow& window);
	void CoinDraw(sf::RenderWindow& window);
	void UIDraw(sf::RenderWindow& window);

	// RESET FUNCTIONS
	void GameReset();
};

