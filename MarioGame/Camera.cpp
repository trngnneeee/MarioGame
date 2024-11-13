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
	// Resize the aspect of the window everytime user resize the window
	float aspect = (float)windowSize.x / (float)windowSize.y;
	if (aspect < 1.0f)
		viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	else
		viewSize = sf::Vector2f(zoomLevel * aspect, zoomLevel);
	return sf::View(position, viewSize);
}

sf::View Camera::GetUIView()
{
	float aspect = viewSize.x / viewSize.y;
	viewUISize = sf::Vector2f(100.0f, 100.0f / aspect);
	return sf::View(sf::Vector2f(), viewUISize);
}
