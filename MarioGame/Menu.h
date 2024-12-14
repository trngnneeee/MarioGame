#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
private:
	// Font
	sf::Font font;

	// Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	// Map button
	sf::RectangleShape level1Button;
	sf::Text level1Text;

	sf::RectangleShape exitButton;
	sf::Text exitText;


public:
	// Functions
	void Begin(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	int HandleInput(sf::RenderWindow& window);
};

