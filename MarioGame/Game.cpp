#include "Game.h"
#include "Map.h"
#include "Mario.h"

Map map(1.0f); 
Camera camera(20.0f);

Mario mario;

void Begin(const sf::Window& window)
{	
	// Init map
	sf::Image image;
	image.loadFromFile("map.png");
	map.Begin();
	mario.position =  map.CreateFromImage(image); 
	map.Update(); // Update the collision box of Map
	
	// Init mario
	mario.Begin();
}

void Update(float deltaTime)
{
	// Set the starting position of camera is the spawning point of Mario
	camera.position = mario.position;

	mario.Update(deltaTime, map);
}

void Render(sf::RenderWindow& window)
{
	map.Draw(window);
	mario.Draw(window);
}
