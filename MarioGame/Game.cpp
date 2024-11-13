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
// Prompt for points
sf::Font font;
sf::Text prompt("Points: ", font);

// Menu
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

	// Init prompt
	if (!font.loadFromFile("./resources/font/BeVietnamPro-ExtraBold.ttf"))
		return;
	prompt.setFillColor(sf::Color::White);
	prompt.setOutlineColor(sf::Color::Black);
	prompt.setOutlineThickness(1.0f);
	prompt.setScale(0.1f, 0.1f);
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

	// Erase enemies that have died
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		if (((*it)->getDieStatus() == true) && ((*it)->getDieTime() <= 0))
		{
			it = enemies.erase(it);  // Erase the enemy and move iterator to the next element
		}
		else
			++it;  // Move to the next enemy if the current one isn't dead
	}
}

void Render(sf::RenderWindow& window)
{
	background.Draw(window);
	map.Draw(window);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw(window);
	}
	mario.Draw(window);
}

void RenderUI(sf::RenderWindow& window)
{
	prompt.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
	prompt.setString("Points: " + std::to_string(mario.getPoints()));
	window.draw(prompt);
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
