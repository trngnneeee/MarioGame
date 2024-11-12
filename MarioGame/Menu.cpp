#include "Menu.h"

void Menu::Begin(sf::RenderWindow& window)
{
	// Load font
	if (!font.loadFromFile("./resources/font/BeVietnamPro-ExtraBold.ttf"))
		return;

	// Load background
	if (!backgroundTexture.loadFromFile("./resources/background/menu-background.png"))
		return;

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		window.getSize().x / backgroundSprite.getLocalBounds().width,
		window.getSize().y / backgroundSprite.getLocalBounds().height
	);

	// Init title
	title = sf::Text("Mario Game", font, 70);
	title.setFillColor(sf::Color::White);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, window.getSize().y / 2 - 300);

	// Init prompt
	prompt = sf::Text("Press Enter to start.", font, 30);
	prompt.setFillColor(sf::Color::White);
	prompt.setPosition(window.getSize().x / 2 - prompt.getGlobalBounds().width / 2, window.getSize().y / 2 - 100);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(title);
	window.draw(prompt);
	window.display();
}
