#include "MapTransition.h"
#include <iostream>

MapTransition::MapTransition()
	: timer(2.0f), currentMapType(1)
{
}

void MapTransition::Begin()
{
	texture.loadFromFile("./resources/MapTransition/mapTransition" + std::to_string(currentMapType) + ".png");
}

void MapTransition::Update(float deltaTime)
{
	timer -= deltaTime;
	sprite.setScale(5.0f, 5.0f);
}

void MapTransition::Draw(sf::RenderWindow& window)
{
	sprite.setTexture(texture);
	window.draw(sprite);
}

void MapTransition::Reset()
{
	currentMapType = 1;
	timer = 2.0f;
}

float MapTransition::getTimer()
{
	return timer;
}

void MapTransition::setTimer(const float& value)
{
	timer = value;
}

int MapTransition::getMapType()
{
	return currentMapType;
}

void MapTransition::setMapType(const int& value)
{
	currentMapType = value;
}


