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
	image.loadFromFile("map.png"); // Load the map from image
	
	// Take Mario position from the return value
	mario.position =  map.CreateFromImage(image); 
}

void Update(float deltaTime)
{
	// Set the starting position of camera is the spawning point of Mario
	camera.position = mario.position;
	mario.Update(deltaTime, map);
}

void Render(Renderer& renderer)
{
	map.Draw(renderer); // draw Map that load from file
	mario.Render(renderer); // draw Mario that load from file
}
