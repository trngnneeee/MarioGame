#include "Game.h"
#include "Map.h"
#include "Mario.h"
#include "Background.h"
#include "EnemyList.h"
#include "Menu.h"
#include "UICounter.h"
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
	background.Begin(window, camera.zoomLevel);

	// Init UICounter 
	UI.Begin();

	// Init music
	music.openFromFile("./resources/soundEffect/music.ogg");
	music.setLoop(true);
	music.play();	
}

void Update(float deltaTime, bool& isDead)
{
	// Update camera
	camera.position = mario.getPosition();
	// Update Mario
	mario.Update(deltaTime, map, enemies, isDead);
	// Update enemies
	enemies.Update(deltaTime, map);
	// Update background
	//background.Update(mario.position);
}

void Render(sf::RenderWindow& window)
{
	//background.Draw(window);
	map.Draw(window);
	enemies.Draw(window);
	mario.Draw(window);
}

void RenderUI(sf::RenderWindow& window)
{
	UI.Update(camera, mario.getPoints());
	UI.Draw(window);
}

void BeginMenu(sf::RenderWindow& window)
{
	menu.Begin(window);
}

void RenderMenu(sf::RenderWindow& window)
{
	menu.Draw(window);
}

void Reset()
{
	music.stop();
	map.Reset();
	mario.Reset();
	enemies.Reset();
}
