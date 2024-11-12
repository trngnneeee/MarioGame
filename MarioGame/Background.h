#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Mario.h"
class Background
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	void Begin();
	void Update(Camera camera, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
};

