#include "Bird.h"

Bird* Bird::clone() const
{
	return new Bird(*this);
}

void Bird::Begin(const sf::Vector2f& position)
{
	for (int i = 0; i < 2; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Bird/bird" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 2; i++)
	{
		runAnimation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	deadTexture.loadFromFile("./resources/textures/Bird/birdDead.png");
	this->position = position;
	sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);
	velocity = sf::Vector2f(-4.0f, 4.0f);
	maxRangeX = position.x + 5.0f;
	minRangeX = position.x - 5.0f;
	maxRangeY = 16.0f;
	minRangeY = 2.0f;
}

void Bird::Update(float deltaTime, const Map& map)
{
	if (HandleDead(deltaTime)) return;
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	position.y += velocity.y * deltaTime;
	position.x += velocity.x * deltaTime;
	if (position.y <= minRangeY || position.y >= maxRangeY)
		velocity.y = -velocity.y;
	if (position.x <= minRangeX || position.x >= maxRangeX)
		velocity.x = -velocity.x;
	sprite.setTexture(*runAnimation.update(deltaTime));
	UpdateScale();
	dieTime = 2.0f;
}

void Bird::UpdateScale()
{
	if (velocity.x < 0)
	{
		sprite.setOrigin(0, 0);
		sprite.setScale(sf::Vector2f(0.9f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
	}
	else
	{
		sprite.setOrigin(textures[0].getSize().x, 0);
		sprite.setScale(sf::Vector2f(0.9f / textures[0].getSize().x * -1, 1.0f / textures[0].getSize().y));
	}
}

bool Bird::HandleDead(const float& deltaTime)
{
	if (isDead)
	{
		position.y -= v * deltaTime;
		v += tmpGravity * deltaTime;
		sprite.setTexture(deadTexture);
		dieTime -= deltaTime;
		return true;
	}
	return false;
}

sf::FloatRect Bird::getCollisionBox() const
{
	return collisionBox;
}
