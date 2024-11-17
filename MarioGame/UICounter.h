#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include "Camera.h"
#include "Mario.h"
#include "Animation.h"

class UICounter
{
private:
	sf::Font font;
	sf::Text overallPoint;

	sf::Text marioLife;
	sf::Texture marioTexture;
	sf::Sprite marioSprite;

	sf::Text timer;
	sf::Text worldNum;

	sf::Texture coinTexture;
	sf::Sprite coinSprite;
	sf::Text coinCounter;
public:
	UICounter();

	void Begin();
	void Update(float deltaTime, Camera camera, const int& points, const int& life, const int& gameTime);
	void Draw(sf::RenderWindow& window);
};

