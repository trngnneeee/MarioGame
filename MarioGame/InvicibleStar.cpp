#include "InvicibleStar.h"

void InvicibleStar::Begin(sf::Vector2f starPosition)
{
	// Init texture
	if (!texture.loadFromFile("./resources/textures/star.png"))
		return;
	sprite.setScale(1.0f / texture.getSize().x, 1.0f / texture.getSize().y);
	sprite.setTexture(texture);

	// Init position
	position = starPosition;
	hiddenBoxPosition = starPosition.y;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / texture.getSize().x,
		1.0f / texture.getSize().y
	);
}
