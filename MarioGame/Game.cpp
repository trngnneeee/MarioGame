#include "Map.h"
#include "Mario.h"
#include "Background.h"
#include "Menu.h"
#include "UICounter.h"
#include "Game.h"
#include "Goombas.h"
#include "Koopa.h"
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

sf::Music music;
sf::Music deadMusic;
bool deadMusicIsPlay;

float timeAccumulator;
int gameTime;

void Begin(sf::RenderWindow& window)
{	
	std::vector<sf::Vector2f> goombasPosition;
	std::vector<sf::Vector2f> koopaPosition;
	sf::Vector2f marioPosition;

	// Init map
	map.Begin();
	map.CreateFromImage(marioPosition, goombasPosition, koopaPosition); 

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
	
	// Init background
	background.Begin(window, camera.zoomLevel, map);

	// Init UICounter 
	UI.Begin();

	// Init music
	music.openFromFile("./resources/soundEffect/music.ogg");
	music.setLoop(true);
	music.play();	
	deadMusic.openFromFile("./resources/soundEffect/dead.mp3");
	deadMusicIsPlay = false;

	// Init time
	gameTime = 300;
	timeAccumulator = 0;
}

void BeginMenu(sf::RenderWindow& window)
{
	menu.Begin(window);
}

void Update(float deltaTime, GameState& gameState, sf::RenderWindow& window)
{
	// Update map
	map.Update(deltaTime);
	// Update camera
	camera.position = mario.getPosition();
	// Update Mario
	for (int i = 0; i < goombas.size(); i++)
	{
		if (goombas[i]->getDieStatus() == false && goombas[i]->getDieByKoopaStatus() == false && mario.goombasCollision(*goombas[i]))
		{
			mario.setDeadStatus(true);
		}
	}
	for (int i = 0; i < koopas.size(); i++)
	{
		if (koopas[i]->getDieStatus() == false && mario.koopaCollision(*koopas[i]))
		{
			if (koopas[i]->getInShellStatus() == false)
				mario.setDeadStatus(true);
			else
				mario.handleKoopaKick(deltaTime, *koopas[i]);
			
		}
	}
	mario.Update(deltaTime, map);
	// Update Goombas
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
		goombas[i]->Update(deltaTime, map);
	}
	for (auto it = goombas.begin(); it != goombas.end();)
	{
		if (((*it)->getDieStatus() == true) && ((*it)->getDieTime() <= 0))
			it = goombas.erase(it);
		else
			++it;
	}
	// Update Koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		// Collision with Goomba
		for (int j = 0; j < goombas.size(); j++)
		{
			if (goombas[j]->koopaCollision(*koopas[i]))
				goombas[j]->setDieByKoopaStatus(true);
		}
		// Collision with other koopa
		for (int j = 0; j < koopas.size(); j++)
		{
			if (i != j)
			{
				if (koopas[i]->teamCollision(*koopas[j]))
					koopas[j]->setDieStatus(true);
			}
		}
		koopas[i]->Update(deltaTime, map);
	}
	for (auto it = koopas.begin(); it != koopas.end();)
	{
		if (((*it)->getDieStatus() == true) && ((*it)->getDieTime() <= 0))
			it = koopas.erase(it);
		else
			++it;
	}
	// Update time
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

void Render(sf::RenderWindow& window)
{
	window.setView(camera.GetView(window.getSize(), map.getCellSize() * map.getGrid().size()));
	background.Draw(window);
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
}

void RenderUI(sf::RenderWindow& window, float deltaTime)
{
	window.setView(camera.GetUIView());
	int displayedTime = static_cast<int>(std::ceil(gameTime)); // Round up for display
	UI.Update(deltaTime, camera, mario.getPoints(), mario.getLife(), displayedTime);
	UI.Draw(window);
}

void RenderMenu(sf::RenderWindow& window)
{
	menu.Draw(window);
}

void Reset()
{
	map.Reset();
	mario.Reset();
	// Reset enemy
	for (int i = 0; i < goombas.size(); i++)
	{
		delete goombas[i];
	}
	goombas.clear();
	for (int i = 0; i < koopas.size(); i++)
	{
		delete koopas[i];
	}
	koopas.clear();
	// Reset music
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
