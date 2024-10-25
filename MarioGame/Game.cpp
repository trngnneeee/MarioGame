#include "Game.h"
#include "Map.h"
#include "Mario.h"

Map map(1.0f); 
Camera camera(20.0f);

Mario mario;

void Begin(const sf::Window& window)
{	
	// Add the map
	sf::Image image;
	image.loadFromFile("map.png");
	
	// Take Mario position from the return value
	mario.position =  map.CreateFromImage(image); 
	mario.Begin();
	map.Begin();
}

void Update(float deltaTime)
{
	// Set the starting position of camera is the spawning point of Mario
	camera.position = mario.position;
	mario.Update(deltaTime);
}

void Render(sf::RenderWindow& window)
{
	map.Draw(window);
	mario.Draw(window);
}
