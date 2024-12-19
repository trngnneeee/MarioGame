#include "BrickParticle.h"

BrickParticle::BrickParticle()
	: animation(0.4f), gravity(40.0f), duration(2.0f), timer(0.0f)
{
}

void BrickParticle::Begin(const sf::Vector2f& position, const sf::Vector2f& velocity)
{
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/BrickParticle/item" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 4; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	this->position = position;
	this->velocity = velocity;
}

void BrickParticle::Update(const float& deltaTime)
{
	timer += deltaTime;
	if (timer <= duration)
	{
		velocity.y += 9.8f * deltaTime;
		position += velocity * deltaTime;
		sprite.setTexture(*animation.update(deltaTime));
		sprite.setScale(sf::Vector2f(0.5f / textures[0].getSize().x, (0.5f / textures[0].getSize().y)));
	}
}

void BrickParticle::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}


void BrickParticle::Reset()
{
	animation.Reset();
	textures.clear();
}

bool BrickParticle::isTimeOut()
{
	return timer >= duration;
}
