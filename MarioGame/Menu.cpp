#include "Menu.h"

void Menu::Begin(sf::RenderWindow& window)
{
	// Load font
	if (!font.loadFromFile("./resources/font/IntroRustG-Base2Line.otf"))
		return;

	// Load Character selection background
	if (!backgroundTexture.loadFromFile("./resources/background/backgroundCharacterSelect.png"))
		return;

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		window.getSize().x / backgroundSprite.getLocalBounds().width,
		window.getSize().y / backgroundSprite.getLocalBounds().height
	);

	sf::Color backgroundColor(148, 148, 255, 255);
	level1Button.setSize(sf::Vector2f(180, 50));
	level1Button.setFillColor(backgroundColor);
	level1Button.setOutlineColor(sf::Color::White);
	level1Button.setOutlineThickness(5.0f);
	level1Button.setPosition(window.getSize().x / 2 - level1Button.getSize().x / 2, window.getSize().y / 2 + 180);

	level1Text = sf::Text("Play", font, 35);
	level1Text.setFillColor(sf::Color::White);
	level1Text.setPosition
	(
		level1Button.getPosition().x + (level1Button.getSize().x - level1Text.getGlobalBounds().width) / 2,
		level1Button.getPosition().y + (level1Button.getSize().y - level1Text.getGlobalBounds().height) / 2 - 10
	);

	exitButton.setSize(sf::Vector2f(180, 50));
	exitButton.setFillColor(backgroundColor);
	exitButton.setOutlineColor(sf::Color::White);
	exitButton.setOutlineThickness(5.0f);
	exitButton.setPosition(window.getSize().x / 2 - exitButton.getSize().x / 2, window.getSize().y / 2 + 260);

	exitText = sf::Text("Exit", font, 35);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(
		exitButton.getPosition().x + (exitButton.getSize().x - exitText.getGlobalBounds().width) / 2,
		exitButton.getPosition().y + (exitButton.getSize().y - exitText.getGlobalBounds().height) / 2 - 10
	);

	index = sf::CircleShape(30, 3);
	index.setRotation(180);
	index.setPosition(360, 260);
	index.setFillColor(sf::Color::Red);

}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	window.draw(level1Button);
	window.draw(level1Text);

	window.draw(exitButton);
	window.draw(exitText);

	window.draw(index);
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