#include "Menu.h"
#include <iostream>

void Menu::Begin(sf::RenderWindow& window)
{
	// Load font
	if (!font.loadFromFile("./resources/font/IntroRustG-Base2Line.otf"))
		return;

	// Load Character selection background
	if (!backgroundTexture.loadFromFile("./resources/background/backgroundCharacterSelect.png"))
		return;

	// Load character texture

	if (!characterTexture[0].loadFromFile("./resources/textures/Mario/marioBig.png"))
		return;

	if (!characterTexture[1].loadFromFile("./resources/textures/Luigi/marioBig.png"))
		return;

	if (!characterTexture[2].loadFromFile("./resources/textures/FireMario/marioBig.png"))
		return;

	characterName[0] = sf::Text("Mario", font, 70);
	characterName[1] = sf::Text("Luigi", font, 70);
	characterName[2] = sf::Text("FireMario", font, 70);

	sf::Color backgroundColor(148, 148, 255, 255);

	level1Button.setSize(sf::Vector2f(180, 50));
	level1Button.setFillColor(backgroundColor);
	level1Button.setOutlineColor(sf::Color::White);
	level1Button.setOutlineThickness(5.0f);

	level1Text = sf::Text("Play", font, 35);
	level1Text.setFillColor(sf::Color::White);


	exitButton.setSize(sf::Vector2f(180, 50));
	exitButton.setFillColor(backgroundColor);
	exitButton.setOutlineColor(sf::Color::White);
	exitButton.setOutlineThickness(5.0f);

	exitText = sf::Text("Exit", font, 35);
	exitText.setFillColor(sf::Color::White);

	leftButton = sf::CircleShape(60, 3);
	leftButton.setRotation(270);
	leftButton.setOutlineColor(sf::Color::Black);
	leftButton.setOutlineThickness(5.0f);
	leftButton.setFillColor(sf::Color::White);

	rightButton = sf::CircleShape(60, 3);
	rightButton.setRotation(90);
	rightButton.setOutlineColor(sf::Color::Black);
	rightButton.setOutlineThickness(5.0f);
	rightButton.setFillColor(sf::Color::White);

	index = 0;

	Update(window);
}

void Menu::Update(sf::RenderWindow& window)
{
	// Set position
	sf::View view = window.getView();
	sf::Vector2f viewCenter = view.getCenter();

	float centerX = viewCenter.x - 100;
	float centerY = viewCenter.y - 100;


	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		window.getSize().x / backgroundSprite.getLocalBounds().width,
		window.getSize().y / backgroundSprite.getLocalBounds().height
	);

	for (int i = 0; i < 3; i++)
	{
		characterSprite[i].setTexture(characterTexture[i]);
		characterSprite[i].setScale
		(
			(window.getSize().x / 6) / characterSprite[0].getLocalBounds().width,
			(window.getSize().y / 6) / characterSprite[0].getLocalBounds().height
		);
		characterSprite[i].setPosition
		(
			centerX, centerY
		);

		characterName[i].setFillColor(sf::Color::Black);
		characterName[i].setOrigin
		(
			characterName[i].getGlobalBounds().width / 2,
			characterName[i].getGlobalBounds().height / 2
		);
		characterName[i].setPosition
		(
			window.getSize().x / 2, window.getSize().y / 5
		);
	}

	level1Button.setPosition(window.getSize().x / 2 - level1Button.getSize().x / 2, window.getSize().y / 2 + 180);

	level1Text.setPosition
	(
		level1Button.getPosition().x + (level1Button.getSize().x - level1Text.getGlobalBounds().width) / 2,
		level1Button.getPosition().y + (level1Button.getSize().y - level1Text.getGlobalBounds().height) / 2 - 10
	);

	exitButton.setPosition(window.getSize().x / 2 - exitButton.getSize().x / 2, window.getSize().y / 2 + 260);

	exitText.setPosition
	(
		exitButton.getPosition().x + (exitButton.getSize().x - exitText.getGlobalBounds().width) / 2,
		exitButton.getPosition().y + (exitButton.getSize().y - exitText.getGlobalBounds().height) / 2 - 10
	);

	leftButton.setOrigin
	(
		leftButton.getGlobalBounds().width / 2,
		leftButton.getGlobalBounds().height / 2
	);

	leftButton.setPosition
	(
		window.getSize().x / 4,
		window.getSize().y / 2
	);

	rightButton.setOrigin
	(
		rightButton.getGlobalBounds().width / 2,
		rightButton.getGlobalBounds().height / 2
	);

	rightButton.setPosition
	(
		window.getSize().x / 2 + window.getSize().x / 4,
		window.getSize().y / 2
	);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	window.draw(level1Button);
	window.draw(level1Text);

	window.draw(exitButton);
	window.draw(exitText);

	window.draw(leftButton);
	window.draw(rightButton);

	window.draw(characterDisplay);
	window.draw(nameDisplay);
}

int Menu::HandleInput(sf::Event& event, sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

	sf::Color backgroundColor(148, 148, 255, 255);
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (rightButton.getGlobalBounds().contains(worldPos))
		{
			if (index == 2)
				index = 0;
			else
				index++;
		}

		else if (leftButton.getGlobalBounds().contains(worldPos))
		{
			if (index == 0)
				index = 2;
			else
				index--;
		}

	}

	characterDisplay = characterSprite[index];
	nameDisplay = characterName[index];

	if (level1Button.getGlobalBounds().contains(worldPos))
	{

		level1Button.setFillColor(sf::Color::Blue);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return index;
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
			return 4;
		}
	}
	else
	{
		exitButton.setFillColor(backgroundColor);
	}

	return 5;
}