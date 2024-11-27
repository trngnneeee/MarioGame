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

	// Init Level 1 button
	level1Button.setSize(sf::Vector2f(200, 50));
	level1Button.setFillColor(sf::Color::Black);
	level1Button.setPosition(window.getSize().x / 2 - level1Button.getSize().x / 2, window.getSize().y / 2);
	level1Text = sf::Text("Map 1", font, 30);
	level1Text.setFillColor(sf::Color::White);
	level1Text.setPosition(
		level1Button.getPosition().x + (level1Button.getSize().x - level1Text.getGlobalBounds().width) / 2,
		level1Button.getPosition().y + (level1Button.getSize().y - level1Text.getGlobalBounds().height) / 2 - 5
	);

	// Init Level 2 button
	level2Button.setSize(sf::Vector2f(200, 50));
	level2Button.setFillColor(sf::Color::Black);
	level2Button.setPosition(window.getSize().x / 2 - level2Button.getSize().x / 2, window.getSize().y / 2 + 70);
	level2Text = sf::Text("Map 2", font, 30);
	level2Text.setFillColor(sf::Color::White);
	level2Text.setPosition(
		level2Button.getPosition().x + (level2Button.getSize().x - level2Text.getGlobalBounds().width) / 2,
		level2Button.getPosition().y + (level2Button.getSize().y - level2Text.getGlobalBounds().height) / 2 - 5
	);

	// Init Level 3 button
	level3Button.setSize(sf::Vector2f(200, 50));
	level3Button.setFillColor(sf::Color::Black);
	level3Button.setPosition(window.getSize().x / 2 - level3Button.getSize().x / 2, window.getSize().y / 2 + 140);
	level3Text = sf::Text("Map 3", font, 30);
	level3Text.setFillColor(sf::Color::White);
	level3Text.setPosition(
		level3Button.getPosition().x + (level3Button.getSize().x - level3Text.getGlobalBounds().width) / 2,
		level3Button.getPosition().y + (level3Button.getSize().y - level3Text.getGlobalBounds().height) / 2 - 5
	);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);
	window.draw(title);
	window.draw(prompt);

	window.draw(level1Button);
	window.draw(level1Text);

	window.draw(level2Button);
	window.draw(level2Text);

	window.draw(level3Button);
	window.draw(level3Text);
	window.display();
}

int Menu::HandleInput(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	// Check if the mouse is over Level 1 button
	if (level1Button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}

	if (level2Button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 2;
		}
	}

	if (level3Button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 3;
		}
	}
}