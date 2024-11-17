#include "Camera.h"

// Constructor
Camera::Camera(float zoomLevel)
	: zoomLevel(zoomLevel)
{	
}

sf::Vector2f Camera::GetViewSize()
{
	return viewSize;
}

sf::Vector2f Camera::GetViewUISize()
{
	return viewUISize;
}

// Functions
sf::View Camera::GetView(sf::Vector2u windowSize)
{
	float aspect = (float)windowSize.x / (float)windowSize.y;

	position.x = std::max(12.5f, std::min(position.x, 800.0f - 12.5f)); // keeping view centered within 100 units horizontally

	position.y = 8.0f;

	if (aspect < 1.0f)
		viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	else
		viewSize = sf::Vector2f(zoomLevel * aspect, zoomLevel);
	return sf::View(sf::Vector2f(position.x, position.y), viewSize);
}

sf::View Camera::GetUIView()
{
	float aspect = viewSize.x / viewSize.y;
	viewUISize = sf::Vector2f(100.0f, 100.0f / aspect);
	return sf::View(sf::Vector2f(), viewUISize);
}
