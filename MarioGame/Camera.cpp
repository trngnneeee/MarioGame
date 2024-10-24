#include "Camera.h"

// Constructor
Camera::Camera(float zoomLevel)
	: zoomLevel(zoomLevel)
{	
}

// Functions
sf::View Camera::GetView(sf::Vector2u windowSize)
{
	// Resize the aspect of the window everytime user resize the window
	float aspect = (float)windowSize.x / (float)windowSize.y;
	sf::Vector2f size;
	if (aspect < 1.0f)
		size = sf::Vector2f(zoomLevel, zoomLevel / aspect);
	else
		size = sf::Vector2f(zoomLevel * aspect, zoomLevel);

	return sf::View(position, size);
}
