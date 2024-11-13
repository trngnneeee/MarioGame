#include "Enemy.h"
#include <iostream>


Enemy::Enemy()
	:runAnimation(0.2f), velocity(3.0f), isDefeat(false), dieTime(3.0f)
{	
}

void Enemy::Begin()
{
	// Load texture
	if (!texture[0].loadFromFile("./resources/textures/enemy1.png"))
	{
		std::cerr << "Failed to load enemy1.png" << std::endl;
		return;
	}
	if (!texture[1].loadFromFile("./resources/textures/enemy2.png"))
	{
		std::cerr << "Failed to load enemy1.png" << std::endl;
		return;
	}

	runAnimation.addFrame(Frame(&texture[0], 0.1f));
	runAnimation.addFrame(Frame(&texture[1], 0.2f));

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / texture[0].getSize().x,
		1.0f / texture[0].getSize().y
	);

	sprite.setScale(sf::Vector2f(1.0f / texture[0].getSize().x, 1.0f / texture[0].getSize().y));
}

void Enemy::Update(float deltaTime, const Map& map, const std::vector<Enemy*>& enemies)
{
	// Check Collision
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	sf::Vector2f newPosition = position;
	newPosition.x -= velocity * deltaTime;
	collisionBox.left = newPosition.x;
	collisionBox.top = position.y;
	if (!mapCollision(map)) {
		position.x = newPosition.x;
	}
	else velocity = -velocity;

	// Alliance collision
	for (int i = 0; i < enemies.size(); i++)
	{
		if (*this != *enemies[i])
		{
			collisionBox.left = position.x;
			collisionBox.top = position.y;
			if (this->teamCollision(*enemies[i]))
				velocity = -velocity;
		}
	}

	if (isDefeat == false)
		sprite.setTexture(*runAnimation.update(deltaTime));
	else
	{
		sprite.setTexture(texture[0]);
		dieTime -= deltaTime * 1.0f;
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (isDefeat == false)
		sprite.setPosition(position);
	else
	{
		if (dieTime > 0)
			sprite.setPosition(position.x, position.y + 0.75f);
	}
	window.draw(sprite);
}

bool Enemy::mapCollision(const Map& map)
{
	for (int i = 0; i < map.collisionBoxList.size(); i++)
	{
		for (int j = 0; j < map.collisionBoxList[i].size(); j++)
		{
			if (collisionBox.intersects(map.collisionBoxList[i][j]) && (map.grid[i][j] == 1 || map.grid[i][j] == 2 || map.grid[i][j] == 4))
				return true;
		}
	}
	return false; // No collision
}

bool Enemy::teamCollision(const Enemy& other)
{
	return (collisionBox.intersects(other.collisionBox) && other.isDefeat == false);
}

void Enemy::defeatHandling()
{
	isDefeat = true;
	sprite.setScale(1.0f / texture[0].getSize().x, 0.25f / texture[0].getSize().y);
	velocity = 0;
}

bool Enemy::getDieStatus()
{
	return isDefeat;
}

float Enemy::getDieTime()
{
	return dieTime;
}

bool Enemy::operator!=(const Enemy& other)
{
	return (collisionBox.getPosition() != other.collisionBox.getPosition() && position != other.position);
}
