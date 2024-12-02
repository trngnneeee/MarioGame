#include "Menu.h"

void Menu::Begin(sf::RenderWindow& window)
{
	// Load font
	if (!font.loadFromFile("./resources/font/IntroRustG-Base2Line.otf"))
		return;

	// Load background
	if (!backgroundTexture.loadFromFile("./resources/background/MenuUi.png"))
		return;

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		window.getSize().x / backgroundSprite.getLocalBounds().width,
		window.getSize().y / backgroundSprite.getLocalBounds().height
	);

	// Init prompt
	prompt = sf::Text("Press play to start", font, 30);
	prompt.setFillColor(sf::Color::White);
	prompt.setPosition(window.getSize().x / 2 - prompt.getGlobalBounds().width / 2, window.getSize().y / 2 + 50);

	// Init Level 1 button
	sf::Color backgroundColor(148, 148, 255, 255);
	level1Button.setSize(sf::Vector2f(200, 50));
	level1Button.setFillColor(backgroundColor);
	level1Button.setOutlineColor(sf::Color::White);
	level1Button.setOutlineThickness(5.0f);
	level1Button.setPosition(window.getSize().x / 2 - level1Button.getSize().x / 2, window.getSize().y / 2 + 120);
	level1Text = sf::Text("Play", font, 40);
	level1Text.setFillColor(sf::Color::White);
	level1Text.setPosition(
		level1Button.getPosition().x + (level1Button.getSize().x - level1Text.getGlobalBounds().width) / 2,
		level1Button.getPosition().y + (level1Button.getSize().y - level1Text.getGlobalBounds().height) / 2 - 10
	);

}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	window.draw(prompt);

	window.draw(level1Button);
	window.draw(level1Text);

}

int Menu::HandleInput(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

	sf::Color backgroundColor(148, 148, 255, 255);

	if (level1Button.getGlobalBounds().contains(worldPos))
	{

		level1Button.setFillColor(sf::Color::Blue);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1; // Clicked and released, game starts
		}
	}
	else
	{
		level1Button.setFillColor(backgroundColor);
	}

	return 2;
}
