#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
class Menu
{
private:
	// Font
	sf::Font font;

	// Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


	// Play button
	sf::RectangleShape level1Button;
	sf::Text level1Text;

	sf::RectangleShape exitButton;
	sf::Text exitText;

	// Character Selection
	// 1 is Mario, 2 is Luigi and 3 is FireMario
	sf::Texture characterTexture[3];
	sf::Sprite characterSprite[3];

	// Display character
	sf::Sprite characterDisplay;

	// Directing
	sf::CircleShape leftButton;
	sf::CircleShape rightButton;

	sf::Text characterName[3];
	sf::Text nameDisplay;

	int index;

public:
	// Functions
	void Begin(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	int HandleInput(sf::Event& event, sf::RenderWindow& window);
};

