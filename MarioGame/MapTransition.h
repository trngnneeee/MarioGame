#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class MapTransition
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float timer;
	int currentMapType;
public:
	// Constructors
	MapTransition();

	// Functions
	void Begin();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	// Setter/Getter
	float getTimer();
	void setTimer(const float& value);
	int getMapType();
	void setMapType(const int& value);
};

