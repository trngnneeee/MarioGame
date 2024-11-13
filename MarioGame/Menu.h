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

	// Play 
	sf::RectangleShape playButton;
	sf::Text playText;
	// Setting
	sf::RectangleShape settingsButton;
	sf::Text settingsText;
public:
	void Begin(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
};

