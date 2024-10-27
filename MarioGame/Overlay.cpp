#include "Overlay.h"

void Overlay::Draw(sf::RenderWindow& window)
{
	window.draw(overlayRect);
}

// Specific for Mario only due to constinuosly change in position
void Overlay::Update(const sf::Vector2f& size, const float& x, const float& y, const sf::Color& color)
{
	overlayRect.setPosition(x, y);
	overlayRect.setSize(size);
	overlayRect.setFillColor(color);
}
