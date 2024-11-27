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
#include <vector>
#include <iostream>

Map map(1.0f); 
Camera camera(16.0f);
Mario mario;
Background background;
UICounter UI;
Menu menu;

// Enemy
std::vector<Goombas*> goombas;
std::vector<Koopa*> koopas;

// Power-up Mushroom
std::vector<PowerUpMushroom*> mushroom;
std::vector<InvicibleStar*> stars;

// Coin
std::vector<Coin*> coins;

sf::Music music;
sf::Music deadMusic;
sf::Music levelUp;
sf::Music win;
bool deadMusicIsPlay;

float timeAccumulator;
int gameTime;

float updateRange = 11.5f;

sf::Vector2f winPosition;

/// Begin
void Begin(sf::RenderWindow& window)
{	
	std::vector<sf::Vector2f> goombasPosition;
	std::vector<sf::Vector2f> koopaPosition;
	std::vector<sf::Vector2f> coinPosition;
	sf::Vector2f marioPosition;

	// Init map
	map.Begin();
	map.CreateFromImage(marioPosition, goombasPosition, koopaPosition, winPosition, coinPosition); 

	// Init mario
	mario.Begin(marioPosition);

	// Init Goombas
	for (int i = 0; i < goombasPosition.size(); i++)
	{
		Goombas* newGoombas = new Goombas;
		newGoombas->Begin(goombasPosition[i]);
		goombas.push_back(newGoombas);
	}
	// Init Koopa
	for (int i = 0; i < koopaPosition.size(); i++)
	{
		Koopa* newKoopa = new Koopa;
		newKoopa->Begin(koopaPosition[i]);
		koopas.push_back(newKoopa);
	}

	// Init coin
	for (int i = 0; i < coinPosition.size(); i++)
	{
		Coin* newCoin = new Coin;
		newCoin->Begin(coinPosition[i]);
		coins.push_back(newCoin);
	}
	
	// Init background
	background.Begin(window, camera.zoomLevel, map);

	// Init UICounter 
	UI.Begin();

	// Init music
	music.openFromFile("./resources/soundEffect/music.ogg");
	music.setLoop(true);
	music.play();	
	deadMusic.openFromFile("./resources/soundEffect/dead.mp3");
	levelUp.openFromFile("./resources/soundEffect/level-up.mp3");
	win.openFromFile("./resources/soundEffect/win.mp3");
	deadMusicIsPlay = false;

	// Init time
	gameTime = 300;
	timeAccumulator = 0;
}

void BeginMenu(sf::RenderWindow& window)
{
	menu.Begin(window);
}

/// Update 
void UpdateMap(float deltaTime)
{
	map.Update(deltaTime);
}

void UpdateCamera()
{
	camera.position = mario.getPosition();
}

void UpdateMario(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars, GameState& gameState)
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
					if (mario.getInvicibleTime() == 0)
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
						if (mario.getInvicibleTime() == 0)
							mario.setInvicibleTime(2.0f);
						mario.setLevelUpStatus(false);
					}
				}
			}
		}
	}
	mario.Update(deltaTime, map, mushroom, stars);
	if (mario.getPosition().x >= winPosition.x)
	{
		music.stop();
		win.play();
		gameState = GameState::GameOver;
		return;
	}
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
			levelUp.play();
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
	if (mario.getDeadStatus() == true)
	{
		music.stop();
		if (!deadMusicIsPlay)
		{
			deadMusic.play();
			deadMusicIsPlay = true;
		}
		if (mario.getDeadTimer() <= 0)
		{
			if (mario.getLife() > 0)
			{
				Reset();
				Begin(window);
				mario.setLife(mario.getLife() - 1);
			}
			if (mario.getLife() <= 0)
				gameState = GameState::GameOver;
		}
	}
}

void Update(float deltaTime, GameState& gameState, sf::RenderWindow& window)
{
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
}

/// Render

void Render(sf::RenderWindow& window)
{
	window.setView(camera.GetView(window.getSize(), map.getCellSize() * map.getGrid().size()));
	background.Draw(window);
	for (int i = 0; i < mushroom.size(); i++)
	{
		mushroom[i]->Draw(window);
	}
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i]->Draw(window);
	}
	map.Draw(window);
	mario.Draw(window);
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->Draw(window);
	}
	for (int i = 0; i < koopas.size(); i++)
	{
		koopas[i]->Draw(window);
	}
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Draw(window);
	}
}

void RenderUI(sf::RenderWindow& window, float deltaTime)
{
	window.setView(camera.GetUIView());
	int displayedTime = static_cast<int>(std::ceil(gameTime)); // Round up for display
	UI.Update(deltaTime, camera, mario.getPoints(), mario.getLife(), mario.getCoin(), displayedTime);
	UI.Draw(window);
}

void RenderMenu(sf::RenderWindow& window)
{
	menu.Draw(window);
}

void Reset()
{
	/// Reset map
	map.Reset();
	/// Reset mario
	mario.Reset();
	/// Reset enemy
	// Reset goomba
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->Reset();
		delete goombas[i];
	}
	goombas.clear();
	// Reset koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		koopas[i]->Reset();
		delete koopas[i];
	}
	koopas.clear();
	/// Reset mushroom
	for (int i = 0; i < mushroom.size(); i++)
	{
		delete mushroom[i];
	}
	mushroom.clear();
	/// Reset star
	for (int i = 0; i < stars.size(); i++)
	{
		delete stars[i];
	}
	stars.clear();
	/// Reset coin
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Reset();
		delete coins[i];
	}
	coins.clear();
	/// Reset music
	music.stop();
	deadMusic.stop();
	deadMusicIsPlay = false;
}

void handleGameOver()
{
	mario.setLife(3);
	mario.setPoints(0);
	Reset();
}
