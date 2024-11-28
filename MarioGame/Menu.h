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

	// Title
	sf::Text title;
	sf::Text prompt;

	// Map button
	sf::RectangleShape level1Button;
	sf::Text level1Text;

	sf::RectangleShape level2Button;
	sf::Text level2Text;

	sf::RectangleShape level3Button;
	sf::Text level3Text;
public:
	// Functions
	void Begin(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	int HandleInput(sf::RenderWindow& window);
};

