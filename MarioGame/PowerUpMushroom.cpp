#include "PowerUpMushroom.h"
#include "Map.h"

void PowerUpMushroom::Begin(sf::Vector2f mushroomPosition)
{
	// Init texture
	for (int i = 0; i < 2; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Mushroom/mushroom" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 2; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	sprite.setScale(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y);

	// Init position
	position = mushroomPosition;
	hiddenBoxPosition = mushroomPosition.y;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		0.9f / textures[0].getSize().x,
		0.9f / textures[0].getSize().y
	);
}