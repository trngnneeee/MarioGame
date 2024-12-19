#include "FloatingScore.h"

FloatingScore::FloatingScore(const int& points, sf::Vector2f startPosition)
	: points(points), position(startPosition), timer(1.0f)
{
	if (!font.loadFromFile("./resources/font/SuperMario256.ttf"))
		return;
	text.setFont(font);
	text.setString(std::to_string(points));
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);
	text.setPosition(position);
	text.setScale(0.02f, 0.02f);
}

void FloatingScore::Update(const float& deltaTime)
{
	position.y -= 5.0f * deltaTime;
	timer -= 2.0f * deltaTime;
}

void FloatingScore::Draw(sf::RenderWindow& window)
{
	text.setPosition(position);
	if (timer > 0)
		window.draw(text);
}

bool FloatingScore::isTimeout()
{
	return timer <= 0;
}
