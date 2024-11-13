#include "Menu.h"

void Menu::Begin(sf::RenderWindow& window)
{
	// Load font
	if (!font.loadFromFile("./resources/font/IntroRustG-Base2Line.otf"))
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
	title = sf::Text("Mario Game", font, 90);
	title.setFillColor(sf::Color::White);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, window.getSize().y / 2 - 150);

	// Init prompt
	prompt = sf::Text("Press Enter to start.", font, 30);
	prompt.setFillColor(sf::Color::White);
	prompt.setPosition(window.getSize().x / 2 - prompt.getGlobalBounds().width / 2, window.getSize().y / 2 - 50);

	// Init Play button
	playButton.setSize(sf::Vector2f(200, 50));
	playButton.setFillColor(sf::Color::Black);
	playButton.setPosition(window.getSize().x / 2 - playButton.getSize().x / 2, window.getSize().y / 2 + 50);
	playText = sf::Text("Play", font, 30);
	playText.setFillColor(sf::Color::White);
	playText.setPosition
	(
		playButton.getPosition().x + (playButton.getSize().x - playText.getGlobalBounds().width) / 2,
		playButton.getPosition().y + (playButton.getSize().y - playText.getGlobalBounds().height) / 2 - 5
	);
	// Init Setting button
	settingsButton.setSize(sf::Vector2f(200, 50));
	settingsButton.setFillColor(sf::Color::Black);
	settingsButton.setPosition(window.getSize().x / 2 - settingsButton.getSize().x / 2, window.getSize().y / 2 + 120);
	settingsText = sf::Text("Settings", font, 30);
	settingsText.setFillColor(sf::Color::White);
	settingsText.setPosition
	(
		settingsButton.getPosition().x + (settingsButton.getSize().x - settingsText.getGlobalBounds().width) / 2,
		settingsButton.getPosition().y + (settingsButton.getSize().y - settingsText.getGlobalBounds().height) / 2 - 5
	);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(title);
	window.draw(prompt);

	window.draw(playButton);
	window.draw(playText);
	window.draw(settingsButton);
	window.draw(settingsText);
	window.display();
}
