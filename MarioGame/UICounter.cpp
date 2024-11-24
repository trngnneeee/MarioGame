#include "UICounter.h"
#include <iostream>

void UICounter::Begin()
{
	if (!font.loadFromFile("./resources/font/SuperMario256.ttf"))
		return;
	overallPoint.setFillColor(sf::Color::White);
	overallPoint.setOutlineColor(sf::Color::Black);
	overallPoint.setOutlineThickness(0.5f);
	overallPoint.setScale(0.1f, 0.1f);

	marioLife.setFillColor(sf::Color::White);
	marioLife.setOutlineColor(sf::Color::Black);
	marioLife.setOutlineThickness(0.5f);
	marioLife.setScale(0.1f, 0.1f);

	timer.setFillColor(sf::Color::White);
	timer.setOutlineColor(sf::Color::Black);
	timer.setOutlineThickness(0.5f);
	timer.setScale(0.1f, 0.1f);

	worldNum.setFillColor(sf::Color::White);
	worldNum.setOutlineColor(sf::Color::Black);
	worldNum.setOutlineThickness(0.5f);
	worldNum.setScale(0.1f, 0.1f);

	coinCounter.setFillColor(sf::Color::White);
	coinCounter.setOutlineColor(sf::Color::Black);
	coinCounter.setOutlineThickness(0.5f);
	coinCounter.setScale(0.1f, 0.1f);

	if (!coinTexture.loadFromFile("./resources/textures/coin1.png"))
		return;
	coinSprite.setTexture(coinTexture);

	if (!marioTexture.loadFromFile("./resources/textures/mario.png"))
		return;
	marioSprite.setTexture(marioTexture);
}

UICounter::UICounter()
{
	overallPoint = sf::Text("MARIO\n", font);
	marioLife = sf::Text("Life: ", font);
	timer = sf::Text("TIME\n", font);
	worldNum = sf::Text("WORLD\n", font);
	coinCounter = sf::Text(": x", font);
}

void UICounter::Update(float deltaTime, Camera camera, const int& points, const int& life, const int& coin, const int& gameTime)
{
	std::ostringstream pointsStream;
	pointsStream << std::setw(6) << std::setfill('0') << points;
	overallPoint.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(2.0f, 6.0f));
	overallPoint.setString("MARIO\n" + pointsStream.str());

	marioLife.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(30.0f, 6.0f));
	marioLife.setString("x " + std::to_string(life));
	marioSprite.setScale(0.1f, 0.1f);
	marioSprite.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(25.0f, 6.0f));

	timer.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(87.0f, 6.0f));
	timer.setString("TIME\n" + std::to_string(gameTime));

	worldNum.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(55.0f, 6.0f));
	worldNum.setString("WORLD: " + std::to_string(1) + "-" + std::to_string(1));

	coinSprite.setScale(0.2f, 0.2f);
	coinSprite.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(25.0f, 10.0f));

	coinCounter.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(30.0f, 10.0f));
	coinCounter.setString("x " + std::to_string(coin));
}

void UICounter::Draw(sf::RenderWindow& window)
{
	window.draw(overallPoint);

	window.draw(marioSprite);
	window.draw(marioLife);

	window.draw(timer);

	window.draw(worldNum);

	window.draw(coinSprite);
	window.draw(coinCounter);
}
