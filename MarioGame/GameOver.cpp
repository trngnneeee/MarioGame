#include "GameOver.h"

void GameOver::Begin()
{
	timer = 5.0f;
	texture.loadFromFile("./resources/MapTransition/gameOver.png");
}

void GameOver::Update(float deltaTime)
{
	timer -= deltaTime;
}

void GameOver::Draw(sf::RenderWindow& window)
{
	sprite.setTexture(texture);
	sprite.setScale(5.0f, 5.0f);
	window.draw(sprite);
}

bool GameOver::isTimeOut()
{
	return timer <= 0;
}
