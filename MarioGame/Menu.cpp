#include "Menu.h"
#include <iostream>

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


	if (!characterTexture[0].loadFromFile("./resources/textures/Mario/marioBig.png"))
	{
		std::cout << "Haha\n";
		return;
	}


	if (!characterTexture[1].loadFromFile("./resources/textures/Luigi/marioBig.png"))
		return;


	if (!characterTexture[2].loadFromFile("./resources/textures/FireMario/marioBig.png"))
		return;

	characterSprite[0].setTexture(characterTexture[0]);

	characterDisplay = characterSprite[0];

	sf::Color backgroundColor(148, 148, 255, 255);

	level1Button.setSize(sf::Vector2f(200, 50));
	level1Button.setFillColor(backgroundColor);
	level1Button.setOutlineColor(sf::Color::White);
	level1Button.setOutlineThickness(5.0f);
	level1Button.setPosition(window.getSize().x / 2 - level1Button.getSize().x / 2, window.getSize().y / 2 + 80);

	level1Text = sf::Text("Play", font, 40);
	level1Text.setFillColor(sf::Color::White);
	level1Text.setPosition
	(
		level1Button.getPosition().x + (level1Button.getSize().x - level1Text.getGlobalBounds().width) / 2,
		level1Button.getPosition().y + (level1Button.getSize().y - level1Text.getGlobalBounds().height) / 2 - 10
	);

	exitButton.setSize(sf::Vector2f(200, 50));
	exitButton.setFillColor(backgroundColor);
	exitButton.setOutlineColor(sf::Color::White);
	exitButton.setOutlineThickness(5.0f);
	exitButton.setPosition(window.getSize().x / 2 - exitButton.getSize().x / 2, window.getSize().y / 2 + 160);

	exitText = sf::Text("Exit", font, 40);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(
		exitButton.getPosition().x + (exitButton.getSize().x - exitText.getGlobalBounds().width) / 2,
		exitButton.getPosition().y + (exitButton.getSize().y - exitText.getGlobalBounds().height) / 2 - 10
	);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	window.draw(level1Button);
	window.draw(level1Text);

	window.draw(exitButton);
	window.draw(exitText);

	window.draw(characterDisplay);
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

	if (exitButton.getGlobalBounds().contains(worldPos))
	{

		exitButton.setFillColor(sf::Color::Blue);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 2;
		}
	}
	else
	{
		exitButton.setFillColor(backgroundColor);
	}

	return 3;
}