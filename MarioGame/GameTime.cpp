#include "GameTime.h"

void GameTime::Begin()
{
	gameTime = 300;
	timeAccumulator = 0;
}

void GameTime::Update(const float& deltaTime)
{
	timeAccumulator += deltaTime;
	while (timeAccumulator >= 1.0f)
	{
		gameTime--;
		timeAccumulator -= 1.0f;
	}
}

int GameTime::getGameTime()
{
	return gameTime;
}

void GameTime::setGameTime(const int& value)
{
	gameTime = value;
}
