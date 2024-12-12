#include "FireFlower.h"

void FireFlower::Begin(sf::Vector2f flowerPosition)
{
	// Init texture
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/FireFlower/flower" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 4; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	sprite.setScale(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y);

	// Init position
	position = flowerPosition;
	hiddenBoxPosition = flowerPosition.y;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);
}
