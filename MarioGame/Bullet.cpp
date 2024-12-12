#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
	: animation(0.2f), appearTime(3.0f), velocity(sf::Vector2f(10.0f, 0.0f)), gravity(20.0f)
{
}

void Bullet::Begin(const sf::Vector2f& position)
{
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Bullet/bullet" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 4; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.05f * (i + 1)));
	}
	this->position = position;
	collisionBox = sf::FloatRect(
		this->position.x,
		this->position.y,
		0.5f,
		0.5f
	);
}

void Bullet::Update(const float& deltaTime, const Map& map)
{
	collisionBox = sf::FloatRect(
		this->position.x,
		this->position.y,
		0.5f,
		0.5f
	);
	appearTime -= deltaTime;
	handleCollisionWithMap(deltaTime, map);
	sprite.setTexture(*animation.update(deltaTime));
}

void Bullet::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(0.5f / textures[0].getSize().x, 0.5f / textures[0].getSize().y));
	window.draw(sprite);
}

void Bullet::Reset()
{
	animation.Reset();
	textures.clear();
}

void Bullet::handleCollisionWithMap(const float& deltaTime, const Map& map)
{
	velocity.y += gravity * deltaTime;
	sf::Vector2f newPosition = position;
	sf::Vector2i collisionAxis(0, 0);
	newPosition.x += velocity.x * deltaTime;
	newPosition.y += velocity.y * deltaTime;
	collisionBox.left = newPosition.x;
	collisionBox.top = newPosition.y;
	if (!mapCollision(map, collisionAxis))
	{
		position = newPosition;
	}
	else
	{
		if (collisionAxis.x == 1)
		{
			velocity.x = -velocity.x * 0.8f;
		}
		if (collisionAxis.y == 1)
		{
			velocity.y = -velocity.y * 0.8f;
		}
	}
	collisionBox.left = position.x;
	collisionBox.top = position.y;
}

bool Bullet::mapCollision(const Map& map, sf::Vector2i& collisionAxis)
{
	std::vector<std::vector<int>> grid = map.getGrid();
	const std::set<int> excludedTiles = { 1, 2, 3, 4, 5, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 42, 44, 45, 46, 47 };

	for (int i = 0; i < map.getCollisionBoxList().size(); i++)
	{
		for (int j = 0; j < map.getCollisionBoxList()[i].size(); j++)
		{
			if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) &&
				excludedTiles.find(grid[i][j]) != excludedTiles.end())
			{
				const sf::FloatRect& tileBox = map.getCollisionBoxList()[i][j];

				float overlapX = std::min(collisionBox.left + collisionBox.width, tileBox.left + tileBox.width) -
					std::max(collisionBox.left, tileBox.left);
				float overlapY = std::min(collisionBox.top + collisionBox.height, tileBox.top + tileBox.height) -
					std::max(collisionBox.top, tileBox.top);

				if (overlapX < overlapY)
				{
					collisionAxis = sf::Vector2i(1, 0); 
				}
				else
				{
					collisionAxis = sf::Vector2i(0, 1); 
				}
				return true;
			}
		}
	}
	return false;
}

float Bullet::getAppearTime()
{
	return appearTime;
}

void Bullet::setAppearTime(const float& value)
{
	appearTime = value;
}

void Bullet::setVelocity(const sf::Vector2f& value)
{
	velocity = value;
}

sf::FloatRect Bullet::getCollisionBox() const
{
	return collisionBox;
}
