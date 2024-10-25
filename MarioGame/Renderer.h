#pragma once
#include "SFML/Graphics.hpp"

class Renderer
{
private:
public:
	sf::Sprite sprite{};
	sf::RenderTarget& target;
	Renderer(sf::RenderTarget& target);
	void Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size);
};

