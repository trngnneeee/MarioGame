#pragma once
#include <SFML/Graphics.hpp>
class GameOver
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float timer;
public:
	// Functions
	void Begin();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	// Setter/Getter
	bool isTimeOut();
};

