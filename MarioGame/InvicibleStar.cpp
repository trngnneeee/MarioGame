#include "InvicibleStar.h"

void InvicibleStar::Begin(sf::Vector2f starPosition)
{
	// Init texture
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Star/star" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 4; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	sprite.setScale(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y);

	// Init position
	position = starPosition;
	hiddenBoxPosition = starPosition.y;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);
}
