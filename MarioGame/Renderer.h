#pragma once
#include "SFML/Graphics.hpp"

class Renderer
{
private:
	sf::Sprite sprite{};
	sf::RenderTarget& target;
public:
	Renderer(sf::RenderTarget& target);
	void Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size);
};

