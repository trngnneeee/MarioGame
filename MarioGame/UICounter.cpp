#include "UICounter.h"
#include <iostream>

void UICounter::Begin()
{
	if (!font.loadFromFile("./resources/font/SuperMario256.ttf"))
		return;
	prompt.setFillColor(sf::Color::White);
	prompt.setOutlineColor(sf::Color::Black);
	prompt.setOutlineThickness(1.0f);
	prompt.setScale(0.1f, 0.1f);
}

UICounter::UICounter()
{
	prompt = sf::Text("Points: ", font);
}

void UICounter::Update(Camera camera, const int& points)
{
	prompt.setPosition(-camera.GetViewUISize() / 2.0f + sf::Vector2f(2.0f, 6.0f));
	prompt.setString("Points: " + std::to_string(points));
}

void UICounter::Draw(sf::RenderWindow& window)
{
	window.draw(prompt);
}
