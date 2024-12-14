#include "FloatingCoin.h"

FloatingCoin::FloatingCoin(sf::Vector2f startPosition)
	: position(startPosition), timer(1.0f), animation(0.2f)
{
	for (int i = 0; i < 10; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Coin/coin" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 10; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.02f * (i + 1)));
	}
	this->startPosition = startPosition;
}

void FloatingCoin::Update(const float& deltaTime)
{
	position.y -= 5.0f * deltaTime;
	sprite.setTexture(*animation.update(deltaTime));
	sprite.setPosition(position);
	timer -= 2.0f * deltaTime;
}

void FloatingCoin::Draw(sf::RenderWindow& window)
{
	sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
	if (timer > 0)
	{
		if (position.y <= startPosition.y - 1.0f)
			window.draw(sprite);
	}
}

bool FloatingCoin::isTimeOut() const
{
	return timer <= 0;
}
