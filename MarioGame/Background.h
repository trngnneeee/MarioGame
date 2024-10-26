#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
class Background
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	void Begin();
	void Draw(sf::RenderWindow& window, Camera camera);
};

