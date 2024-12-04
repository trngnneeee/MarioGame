#pragma once
#include <SFML/Graphics.hpp>
class Camera
{
private:
	sf::Vector2f viewSize{};
	sf::Vector2f viewUISize{};
	float zoomLevel;
	sf::Vector2f position;
public:
	// Constructor
	Camera(float zoomLevel = 1.0f);
	// Setter/Getter
	sf::View GetView(sf::Vector2u windowSize, const float& mapSize);
	sf::View GetUIView(); 
	sf::Vector2f GetViewSize();
	sf::Vector2f GetViewUISize();
	float getZoomlevel();
	void setPosition(const sf::Vector2f& position);
};

