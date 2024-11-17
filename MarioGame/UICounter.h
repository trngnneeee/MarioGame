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
	sf::Text prompt;
	sf::Text prompt2;
	sf::Text prompt3;
	sf::Text prompt4;

	sf::Texture textures;
	sf::Sprite sprite;
	sf::Text coinCounter;
public:
	UICounter();

	void Begin();
	void Update(float deltaTime, Camera camera, const int& points, const int& life, const int& gameTime);
	void Draw(sf::RenderWindow& window);
};

