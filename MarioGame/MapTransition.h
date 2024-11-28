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
	MapTransition();

	void Begin();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	// Setter/Getter
	float getTimer();
	void setTimer(const float& value);
	
	int getMapType();
	void setMapType(const int& value);
};

