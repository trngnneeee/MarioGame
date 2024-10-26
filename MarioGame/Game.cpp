#include "Game.h"
#include "Map.h"
#include "Mario.h"
#include "Background.h"

Map map(1.0f); 
Camera camera(25.0f);
sf::Music music;

Mario mario;
Background background;

void Begin(const sf::Window& window)
{	
	// Init map
	sf::Image image;
	image.loadFromFile("map1.png");
	map.Begin();
	mario.position =  map.CreateFromImage(image); 
	map.Update(); // Update the collision box of Map

	// Init mario
	mario.Begin();

	// Init music
	music.openFromFile("./resources/soundEffect/music.ogg");
	music.setLoop(true);
	music.play();

	// Init background
	background.Begin();
}

void Update(float deltaTime)
{
	camera.position = mario.position;

	mario.Update(deltaTime, map);
}

void Render(sf::RenderWindow& window)
{
	background.Draw(window, camera);
	map.Draw(window);
	mario.Draw(window);
}
