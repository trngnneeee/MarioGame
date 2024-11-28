#include "Map.h"
#include "Mario.h"
#include "Background.h"
#include "Menu.h"
#include "UICounter.h"
#include "Game.h"
#include "Goombas.h"
#include "Koopa.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include "Coin.h"
#include "MapTransition.h"
#include "SoundManagement.h"
#include <vector>
#include <iostream>
#include <string>

// Game menu 
Menu menu;

// Map transition
MapTransition mapTransition;

// Map
Map map(1.0f); 

// Camera
Camera camera(16.0f);

// Mario
Mario mario;

// Background
Background background;

// Counter for coin, mario's life, gametime
UICounter UI;

// Enemy
std::vector<std::unique_ptr<Goombas>> goombas;
std::vector<std::unique_ptr<Koopa>> koopas;

// Hidden box item
std::vector<std::unique_ptr<PowerUpMushroom>> mushroom;
std::vector<std::unique_ptr<InvicibleStar>> stars;

// Coin
std::vector<std::unique_ptr<Coin>> coins;

// Music
//sf::Music music;
//bool musicIsPlay;
//sf::Music deadMusic;
//sf::Music levelUp;
//sf::Music win;
//bool deadMusicIsPlay;

// Game time
float timeAccumulator;
int gameTime;

// Update range
float updateRange;

// Win position
sf::Vector2f winPosition;

/// Begin
void BeginMenu(sf::RenderWindow& window)
{
	menu.Begin(window);
}

void BeginGame(sf::RenderWindow& window)
{	
	std::vector<sf::Vector2f> goombasPosition;
	std::vector<sf::Vector2f> koopaPosition;
	std::vector<sf::Vector2f> coinPosition;
	sf::Vector2f marioPosition;

	BeginMap(marioPosition, winPosition, goombasPosition, koopaPosition, coinPosition);
	BeginMario(marioPosition);
	BeginGoomba(goombasPosition);
	BeginKoopa(koopaPosition);
	BeginCoin(coinPosition);
	BeginBackground(camera.zoomLevel, map);
	BeginMusic();
	BeginGameTime();
	UI.Begin();
	mapTransition.Begin();
}

/// Update 
void UpdateGame(float deltaTime, GameState& gameState, sf::RenderWindow& window)
{
	if (UpdateMapTransition(deltaTime)) return;
	if (!SoundManager::getInstance().getPlayedStatus("main"))
	{
		SoundManager::getInstance().playSound("main");
		SoundManager::getInstance().setPlayedStatus("main", true);
		SoundManager::getInstance().setLoop("main", true);
	}
	UpdateMap(deltaTime);
	UpdateCamera();
	UpdateMario(deltaTime, map, mushroom, stars, gameState);
	UpdateGoomba(deltaTime, map);
	UpdateKoopa(deltaTime, map);
	UpdateMushroom(deltaTime, map);
	UpdateStar(deltaTime, map);
	UpdateCoin(deltaTime);
	UpdateGameTime(deltaTime);
	UpdateGameState(gameState, window);
	// Detect winning
	if (mario.getPosition().x >= winPosition.x)
	{
		handleWining();
		BeginGame(window);
		return;
	}
}

/// Render
void RenderGame(sf::RenderWindow& window)
{
	if (mapTransition.getTimer() > 0)
	{
		RenderMapTransition(window);
		return;
	}

	window.setView(camera.GetView(window.getSize(), map.getCellSize() * map.getGrid().size()));

	RenderBackground(window);
	RenderMushroom(window);
	RenderStar(window);
	RenderMap(window);
	RenderMario(window);
	RenderGoomba(window);
	RenderKoopa(window);
	RenderCoin(window);
}

/// Begin Function
void BeginMap(sf::Vector2f& marioPosition, sf::Vector2f& winPosition, std::vector<sf::Vector2f>& goombasPosition, std::vector<sf::Vector2f>& koopaPosition, std::vector<sf::Vector2f>& coinPosition)
{
	int mapType = mario.getMapArchive();
	std::string mapName = "";
	if (mapType == 1)
		mapName = "map1.png";
	else if (mapType == 2)
		mapName = "map2.png";
	else if (mapType == 3)
		mapName = "map3.png";
	mapTransition.setMapType(mapType);
	map.Begin(mapName);
	map.CreateFromImage(marioPosition, goombasPosition, koopaPosition, winPosition, coinPosition);

	map.CreateCollisionBox();
}

void BeginMario(sf::Vector2f marioPosition)
{
	mario.Begin(marioPosition);

}

void BeginGoomba(std::vector<sf::Vector2f> goombasPosition)
{
	for (int i = 0; i < goombasPosition.size(); i++)
	{
		auto newGoomba = std::make_unique<Goombas>();
		newGoomba->Begin(goombasPosition[i]);
		goombas.push_back(std::move(newGoomba));
	}
}

void BeginKoopa(std::vector<sf::Vector2f> koopaPosition)
{
	for (int i = 0; i < koopaPosition.size(); i++)
	{
		auto newKoopa = std::make_unique<Koopa>();
        newKoopa->Begin(koopaPosition[i]);
        koopas.push_back(std::move(newKoopa));
	}
}

void BeginCoin(std::vector<sf::Vector2f> coinPosition)
{
	for (int i = 0; i < coinPosition.size(); i++)
	{
		auto newCoin = std::make_unique<Coin>();
		newCoin->Begin(coinPosition[i]);
		coins.push_back(std::move(newCoin));
	}
}

void BeginBackground(const float& zoomLevel, const Map& map)
{
	background.Begin(camera.zoomLevel, map);
}

void BeginMusic()
{
	SoundManager& soundManager = SoundManager::getInstance();
	soundManager.loadSound("main", "./resources/soundEffect/music.ogg");
	soundManager.loadSound("dead", "./resources/soundEffect/dead.ogg");
	soundManager.loadSound("levelUp", "./resources/soundEffect/level-up.ogg");
	soundManager.loadSound("win", "./resources/soundEffect/win.ogg");
	soundManager.loadSound("coin", "./resources/soundEffect/coin.ogg");
	soundManager.loadSound("jump", "./resources/soundEffect/jump.wav");
}

void BeginGameTime()
{
	gameTime = 300;
	timeAccumulator = 0;
}


/// Update Function
bool UpdateMapTransition(float deltaTime)
{
	if (mapTransition.getTimer() > 0)
	{
		mapTransition.Update(deltaTime);
		return true;
	}
	else return false;
}

void UpdateMap(float deltaTime)
{
	map.Update(deltaTime);
}

void UpdateCamera()
{
	camera.position = mario.getPosition();
}

void UpdateMario(float deltaTime, Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars, GameState& gameState)
{
	// Collision with goomba
	for (int i = 0; i < goombas.size(); i++)
	{
		if (goombas[i]->getDieStatus() == false && goombas[i]->getDieByKoopaStatus() == false && mario.goombasCollision(*goombas[i]))
		{
			if (mario.getInvicibleTime2() > 0)
				goombas[i]->setDieByKoopaStatus(true);
			else
			{
				if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
					mario.setDeadStatus(true);
				else
				{
					if (mario.getInvicibleTime() <= 0)
						mario.setInvicibleTime(2.0f);
					mario.setLevelUpStatus(false);
				}
			}
		}
	}
	// Collision with koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		if (mario.koopaCollision(*koopas[i]))
		{
			if (!koopas[i]->getInShellStatus())
			{
				if (mario.getInvicibleTime2() > 0)
					koopas[i]->setDieStatus(true);
				else
				{
					if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
						mario.setDeadStatus(true);
					else
					{
						if (mario.getInvicibleTime() <= 0)
							mario.setInvicibleTime(2.0f);
						mario.setLevelUpStatus(false);
					}
				}
			}
		}
	}
	mario.Update(deltaTime, map, mushroom, stars);
}

void UpdateGoomba(float deltaTime, const Map& map)
{
	for (int i = 0; i < goombas.size(); i++)
	{
		for (int j = 0; j < goombas.size(); j++)
		{
			if (i != j)
			{
				if (goombas[i]->teamCollision(*goombas[j]))
				{
					goombas[i]->handleTeamCollision();
					goombas[j]->handleTeamCollision();
				}
			}
		}
		if (mario.distanceX(*goombas[i]) <= updateRange || goombas[i]->getGameState() == true)
		{
			if (goombas[i]->getGameState() == false)
			{
				goombas[i]->setGameState(true);
			}
			goombas[i]->Update(deltaTime, map);
		}
	}
	// Remove die goomba
	goombas.erase(
		std::remove_if(goombas.begin(), goombas.end(),
			[](const auto& goomba) {
				return (goomba->getDieStatus() && goomba->getDieTime() <= 0) ||
					goomba->getPosition().y >= 16.0f;
			}),
		goombas.end());
}

void UpdateKoopa(float deltaTime, const Map& map)
{
	for (int i = 0; i < koopas.size(); i++)
	{
		// Collision with Goomba
		for (int j = 0; j < goombas.size(); j++)
		{
			if (goombas[j]->koopaCollision(*koopas[i]))
			{
				if (goombas[j]->getDieByKoopaStatus() == false)
					mario.setPoints(mario.getPoints() + 200);
				goombas[j]->setDieByKoopaStatus(true);
			}
		}
		// Collision with other koopa
		for (int j = 0; j < koopas.size(); j++)
		{
			if (i != j)
			{
				if (koopas[i]->teamCollision(*koopas[j]))
				{
					if (koopas[j]->getDieStatus() == false)
						mario.setPoints(mario.getPoints() + 200);
					koopas[j]->setDieStatus(true);
				}
			}
		}
		if (mario.distanceX(*koopas[i]) <= updateRange || koopas[i]->getGameState() == true)
		{
			if (koopas[i]->getGameState() == false)
			{
				koopas[i]->setGameState(true);
			}
			koopas[i]->Update(deltaTime, map);
		}
	}
	// Remove die koopa
	koopas.erase(
		std::remove_if(koopas.begin(), koopas.end(),
			[](const auto& koopa) {
				return (koopa->getDieStatus() && koopa->getDieTime() <= 0) ||
					koopa->getPosition().y >= 16.0f;
			}),
		koopas.end());
}

void UpdateMushroom(float deltaTime, const Map& map)
{
	for (int i = 0; i < mushroom.size(); i++)
	{
		if (mario.mushroomCollision(*mushroom[i]) && mushroom[i]->getDeadStatus() == false && mushroom[i]->getOutStatus() == true)
		{
			mario.setPoints(mario.getPoints() + 1000);
			if (!SoundManager::getInstance().getPlayedStatus("levelUp"))
			{
				SoundManager::getInstance().playSound("levelUp");
			}
			if (mario.getLevelUpStatus() == false)
			{
				mario.setLevelUpStatus(true);
				mario.setPosition(sf::Vector2f(mario.getPosition().x, mario.getPosition().y - 1.0f));
			}
			else
				mario.setLife(mario.getLife() + 1);
			mushroom[i]->setDeadStatus(true);
		}
		mushroom[i]->Update(deltaTime, map);
	}
	// Remove die mushroom
	mushroom.erase(
		std::remove_if(mushroom.begin(), mushroom.end(),
			[](const auto& item) {
				return (item->getDeadStatus() && item->getDieTime() <= 0) ||
					item->getPosition().y >= 16.0f;
			}),
		mushroom.end());
}

void UpdateStar(float deltaTime, const Map& map)
{
	for (int i = 0; i < stars.size(); i++)
	{
		if (mario.starCollision(*stars[i]) && stars[i]->getDeadStatus() == false && stars[i]->getOutStatus() == true)
		{
			mario.setPoints(mario.getPoints() + 1000);
			stars[i]->setDeadStatus(true);
			mario.setInvicibleTime2(10.0f);
		}
		stars[i]->Update(deltaTime, map);
	}
	// Remove die star
	stars.erase(
		std::remove_if(stars.begin(), stars.end(),
			[](const auto& star) {
				return (star->getDeadStatus() && star->getDieTime() <= 0) ||
					star->getPosition().y >= 16.0f;
			}),
		stars.end());
}

void UpdateCoin(float deltaTime)
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (mario.coinCollision(*coins[i]))
		{
			if (coins[i]->isCollected() == false)
			{
				mario.setPoints(mario.getPoints() + 100);
				mario.setCoin(mario.getCoin() + 1);
				coins[i]->setCollected(true);
			}
		}
		coins[i]->Update(deltaTime);
	}
	// Remove collected coin
	coins.erase(
		std::remove_if(coins.begin(), coins.end(),
			[](const auto& coin) {
				return coin->isCollected() && coin->getDisapperTime() <= 0;
			}),
		coins.end());
}

void UpdateGameTime(float deltaTime)
{
	timeAccumulator += deltaTime;
	while (timeAccumulator >= 1.0f)
	{
		gameTime--;
		timeAccumulator -= 1.0f;
		if (gameTime < 0)
		{
			mario.setDeadStatus(true);
			gameTime = 0;
		}
	}
}

void UpdateGameState(GameState& gameState, sf::RenderWindow& window)
{
	updateRange = window.getSize().x * 11.5f / 1200;
	if (mario.getDeadStatus() == true)
	{
		SoundManager::getInstance().stopSound("main");
		SoundManager::getInstance().setPlayedStatus("main", false);
		if (!SoundManager::getInstance().getPlayedStatus("dead"))
		{
			SoundManager::getInstance().playSound("dead");
			SoundManager::getInstance().setPlayedStatus("dead", true);
		}
		if (mario.getDeadTimer() <= 0)
		{
			if (mario.getLife() > 0)
			{
				mario.ResetStillLife();
			}
			if (mario.getLife() <= 0)
			{
				ResetGame();
				mario.Reset();
				gameState = GameState::GameOver;
			}
			SoundManager::getInstance().setPlayedStatus("dead", false);
		}
	}
}

void handleWining()
{
	SoundManager::getInstance().stopSound("main");
	SoundManager::getInstance().setPlayedStatus("main", false);
	mario.setMapArchive(mario.getMapArchive() + 1);
	mapTransition.setMapType(mapTransition.getMapType() + 1);
	mapTransition.setTimer(3.0f);
	ResetGame();
}

/// Render Function
void RenderMapTransition(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	mapTransition.Draw(window);
}

void RenderBackground(sf::RenderWindow& window)
{
	background.Draw(window);
}

void RenderMushroom(sf::RenderWindow& window)
{
	for (int i = 0; i < mushroom.size(); i++)
	{
		mushroom[i]->Draw(window);
	}
}

void RenderStar(sf::RenderWindow& window)
{
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i]->Draw(window);
	}
}

void RenderMap(sf::RenderWindow& window)
{
	map.Draw(window);
}

void RenderMario(sf::RenderWindow& window)
{
	mario.Draw(window);
}

void RenderGoomba(sf::RenderWindow& window)
{
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->Draw(window);
	}
}

void RenderKoopa(sf::RenderWindow& window)
{
	for (int i = 0; i < koopas.size(); i++)
	{
		koopas[i]->Draw(window);
	}
}

void RenderCoin(sf::RenderWindow& window)
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Draw(window);
	}
}

void RenderUI(sf::RenderWindow& window, float deltaTime)
{
	if (mapTransition.getTimer() > 0) return;
	window.setView(camera.GetUIView());
	int displayedTime = static_cast<int>(std::ceil(gameTime)); // Round up for display
	UI.Update(deltaTime, camera, mario.getPoints(), mario.getLife(), mario.getCoin(), displayedTime);
	UI.Draw(window);
}

void RenderMenu(sf::RenderWindow& window)
{
	menu.Draw(window);
}

void ResetGame()
{
	/// Reset map
	map.Reset();
	/// Reset enemy
	// Reset goomba
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->Reset();
	}
	goombas.clear();
	// Reset koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		koopas[i]->Reset();
	}
	koopas.clear();
	stars.clear();
	/// Reset coin
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Reset();
	}
	coins.clear();
	/// Reset music
	/*music.stop();
	deadMusic.stop();
	deadMusicIsPlay = false;*/
}
