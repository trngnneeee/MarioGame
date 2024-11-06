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
	map.Begin(); // Generate and archive map + collisionBox into vector

	// Init mario
	mario.position =  map.CreateFromImage(image); 
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
	background.Update(camera);
	mario.Update(deltaTime, map);
}

void Render(sf::RenderWindow& window)
{
	background.Draw(window);
	map.Draw(window);
	mario.Draw(window);
}

void RenderMenu(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("./resources/font/BeVietnamPro-ExtraBold.ttf"))
		return;
	// Background
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("./resources/background/menu-background.png"))
		return;
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		window.getSize().x / backgroundSprite.getLocalBounds().width,
		window.getSize().y / backgroundSprite.getLocalBounds().height
	);

	// Main title
	sf::Text title("Mario Game", font, 50);
	title.setFillColor(sf::Color::White);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, window.getSize().y / 2 - 300);

	// Start
	sf::Text prompt("Start", font, 30);
	prompt.setFillColor(sf::Color::White);
	prompt.setPosition(window.getSize().x / 2 - prompt.getGlobalBounds().width / 2, window.getSize().y / 2 - 100);

	window.clear();
	window.draw(backgroundSprite);
	window.draw(title);
	window.draw(prompt);
	window.display();
}