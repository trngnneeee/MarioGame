#include "Map.h"
#include "Mario.h"
#include "Background.h"
#include "EnemyList.h"
#include "Menu.h"
#include "UICounter.h"
#include "Game.h"
#include <vector>
#include <iostream>

Map map(1.0f); 
Camera camera(16.0f);
EnemyList enemies;
Mario mario;
Background background;
UICounter UI;
Menu menu;

sf::Music music;
sf::Music deadMusic;

float timeAccumulator;
int gameTime;

void Begin(sf::RenderWindow& window)
{	
	std::vector<sf::Vector2f> enemiesPosition;
	sf::Vector2f marioPosition;

	// Init map
	map.Begin();
	map.CreateFromImage(marioPosition, enemiesPosition); 

	// Init mario
	mario.Begin(marioPosition);

	// Init enemy
	enemies.Begin(enemiesPosition);
	
	// Init background
	background.Begin(window, camera.zoomLevel, map);

	// Init UICounter 
	UI.Begin();

	// Init music
	music.openFromFile("./resources/soundEffect/music.ogg");
	deadMusic.openFromFile("./resources/soundEffect/dead.mp3");
	music.setLoop(true);
	music.play();	

	// Init time
	gameTime = 300;
	timeAccumulator = 0;
}

void BeginMenu(sf::RenderWindow& window)
{
	menu.Begin(window);
}

void Update(float deltaTime, bool& gameOverFlag)
{
	// Update map
	map.Update(deltaTime);
	// Update camera
	camera.position = mario.getPosition();
	// Update Mario
	mario.Update(deltaTime, map, enemies, gameOverFlag, music);
	// Update enemies
	enemies.Update(deltaTime, map);
	// Update time
	timeAccumulator += deltaTime;
	while (timeAccumulator >= 1.0f)
	{
		gameTime--;              
		timeAccumulator -= 1.0f;
		if (gameTime < 0)
		{
			gameTime = 0;
			mario.setLife(mario.getLife() - 1);
			gameOverFlag = true;
		}
	}
}

void Render(sf::RenderWindow& window)
{
	window.setView(camera.GetView(window.getSize(), map.getCellSize() * map.getGrid().size()));
	background.Draw(window);
	map.Draw(window);
	enemies.Draw(window);
	mario.Draw(window);
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

void HandleDead(float deltaTime)
{
	mario.HandleDead(deltaTime);
}

bool isEnd()
{
	return mario.getLife() <= 0;
}

void handleEnd()
{
	music.stop();
	deadMusic.play();
	mario.setLife(3);
	mario.setPoints(0);
}

void Reset()
{
	map.Reset();
	mario.Reset();
	enemies.Reset();
}
