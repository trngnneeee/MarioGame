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


	// Play button
	sf::RectangleShape level1Button;
	sf::Text level1Text;

	sf::RectangleShape exitButton;
	sf::Text exitText;

	// 3 characters to select
	//1 for 
	sf::Texture characterTexture[3];
	sf::Sprite characterSprite[3];

	sf::CircleShape index;



public:
	// Functions
	void Begin(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	int HandleInput(sf::RenderWindow& window);
};

