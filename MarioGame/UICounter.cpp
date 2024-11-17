#include "UICounter.h"
#include <iostream>

void UICounter::Begin()
{
	if (!font.loadFromFile("./resources/font/SuperMario256.ttf"))
		return;
	prompt.setFillColor(sf::Color::White);
	prompt.setOutlineColor(sf::Color::Black);
	prompt.setOutlineThickness(0.5f);
	prompt.setScale(0.1f, 0.1f);

	prompt2.setFillColor(sf::Color::White);
	prompt2.setOutlineColor(sf::Color::Black);
	prompt2.setOutlineThickness(0.5f);
	prompt2.setScale(0.1f, 0.1f);

	prompt3.setFillColor(sf::Color::White);
	prompt3.setOutlineColor(sf::Color::Black);
	prompt3.setOutlineThickness(0.5f);
	prompt3.setScale(0.1f, 0.1f);

	prompt4.setFillColor(sf::Color::White);
	prompt4.setOutlineColor(sf::Color::Black);
	prompt4.setOutlineThickness(0.5f);
	prompt4.setScale(0.1f, 0.1f);

	coinCounter.setFillColor(sf::Color::White);
	coinCounter.setOutlineColor(sf::Color::Black);
	coinCounter.setOutlineThickness(0.5f);
	coinCounter.setScale(0.1f, 0.1f);

	if (!textures.loadFromFile("./resources/textures/coin1.png"))
		return;
	sprite.setTexture(textures);
}

UICounter::UICounter()
{
	prompt = sf::Text("MARIO\n", font);
	prompt2 = sf::Text("Life: ", font);
	prompt3 = sf::Text("TIME\n", font);
	prompt4 = sf::Text("WORLD\n", font);
	coinCounter = sf::Text(": x", font);
}

void UICounter::Update(float deltaTime, Camera camera, const int& points, const int& life, const int& gameTime)
{
	std::ostringstream pointsStream;
	pointsStream << std::setw(6) << std::setfill('0') << points;
	prompt.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(2.0f, 6.0f));
	prompt.setString("MARIO\n" + pointsStream.str());

	prompt2.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(25.0f, 6.0f));
	prompt2.setString("Life: " + std::to_string(life));

	prompt3.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(87.0f, 6.0f));
	prompt3.setString("TIME\n" + std::to_string(gameTime));

	prompt4.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(55.0f, 6.0f));
	prompt4.setString("WORLD: " + std::to_string(1) + "-" + std::to_string(1));

	sprite.setScale(0.1f, 0.1f);
	sprite.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(25.0f, 10.0f));

	coinCounter.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(30.0f, 10.0f));
	coinCounter.setString("x " + std::to_string(0));
}

void UICounter::Draw(sf::RenderWindow& window)
{
	window.draw(prompt);
	window.draw(prompt2);
	window.draw(prompt3);
	window.draw(prompt4);
	window.draw(sprite);
	window.draw(coinCounter);
}
