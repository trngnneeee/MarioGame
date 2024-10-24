#include "Renderer.h"

// Constructor
Renderer::Renderer(sf::RenderTarget& target)
	: target(target)
{
}

// Functions
void Renderer::Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size)
{
	sprite.setTexture(texture, true); // For the first texture (brick) its a rectangle -> so when load the mario texture, its also a rectangle -> set true to fixed
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f); // set the middle of the target as the position
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));
	target.draw(sprite);
}
