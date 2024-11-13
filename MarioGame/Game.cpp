#include "Game.h"
#include "Map.h"
#include "Mario.h"
#include "Background.h"
#include "Enemy.h"
#include "Menu.h"
#include <vector>
#include <iostream>

Map map(1.0f); 
Camera camera(25.0f);
sf::Music music;

Mario mario;
std::vector<Enemy*> enemies;
Background background;

Menu menu;

void Begin(const sf::Window& window)
{	
	// Init map
	sf::Image image;
	image.loadFromFile("map2.png");
	map.Begin(); // Generate and archive map + collisionBox into vector

	// Init position for mario and enemy
	std::vector<sf::Vector2f> enemiesPosition;
	map.CreateFromImage(image, mario.position, enemiesPosition); 

	// Init mario
	mario.Begin();

	// Init enemy
	for (int i = 0; i < enemiesPosition.size(); i++) 
	{
		Enemy* newEnemy = new Enemy;
		newEnemy->position = enemiesPosition[i];
		newEnemy->Begin();
		enemies.push_back(newEnemy);
	}

	// Init music
	music.openFromFile("./resources/soundEffect/music.ogg");
	music.setLoop(true);
	music.play();

	// Init background
	background.Begin();
}

void Update(float deltaTime, bool& isDead)
{
	camera.position = mario.position;
	background.Update(camera, mario.position);
	mario.Update(deltaTime, map);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(deltaTime, map, enemies);
		if (mario.enemyCollison(*enemies[i])) isDead = true;
	}
}

void Render(sf::RenderWindow& window)
{
	background.Draw(window);
	map.Draw(window);
	for (int i = 0; i < enemies.size(); i++)
	{
		//enemies[i]->Draw(window);
		if (enemies[i]->getDieStatus() == false)
			enemies[i]->Draw(window);
	}
	mario.Draw(window);
}

void Reset()
{
	music.stop();
	map.Reset();
	mario.Reset();
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();
}
