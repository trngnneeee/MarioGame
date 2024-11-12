#include "Game.h"
#include "Map.h"
#include "Mario.h"
#include "Background.h"
#include "Enemy.h"
#include "Menu.h"

Map map(1.0f); 
Camera camera(25.0f);
sf::Music music;

Mario mario;
Enemy enemy;
Background background;

Menu menu;

void Begin(const sf::Window& window)
{	
	// Init map
	sf::Image image;
	image.loadFromFile("map2.png");
	map.Begin(); // Generate and archive map + collisionBox into vector

	// Init position for mario and enemy
	map.CreateFromImage(image, mario.position, enemy.position); 

	// Init mario
	mario.Begin();

	// Init enemy
	enemy.Begin();

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
	enemy.Update(deltaTime, map);
	if (mario.isDead(enemy))
	{
		isDead = true;
	}
}

void Render(sf::RenderWindow& window)
{
	background.Draw(window);
	map.Draw(window);
	mario.Draw(window);
	enemy.Draw(window);
}

void Reset()
{
	music.stop();
	map.Reset();
}
