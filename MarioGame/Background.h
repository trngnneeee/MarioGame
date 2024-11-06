#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
class Background
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float parallaxFactor = 0.05f; 
public:
	void Begin();
	void Update(Camera camera);
	void Draw(sf::RenderWindow& window);
};

