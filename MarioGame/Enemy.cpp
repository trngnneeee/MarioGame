#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
	:runAnimation(0.2f), isDefeat(false), dieTime(3.0f), gravity(5.0f)
{	
	velocity.x = 3.0f;
	velocity.y = 0.0f;
}

Enemy::~Enemy()
{
	if (score)
		delete score;
}

void Enemy::Begin()
{
	// Init texture
	if (!texture[0].loadFromFile("./resources/textures/enemy1.png"))
		return;
	if (!texture[1].loadFromFile("./resources/textures/enemy2.png"))
		return;

	// Init animation 
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

void Enemy::Update(float deltaTime, const Map& map)
{
	// Update position of Collision box
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	handleMove(deltaTime, map);

	UpdateTextures(deltaTime);

	if (score)
	{
		score->Update(deltaTime);
		if (score->isTimeout())
		{
			delete score;
			score = NULL;
		}
	}
}

void Enemy::handleMove(float deltaTime, const Map& map)
{
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);
}

void Enemy::handleHorizontalMove(float deltaTime, const Map& map)
{
	sf::Vector2f newPosition = position;
	newPosition.x -= velocity.x * deltaTime;

	collisionBox.left = newPosition.x;
	collisionBox.top = position.y;

	if (!mapCollision(map))
		position.x = newPosition.x;
	else
		velocity.x = -velocity.x;
	collisionBox.left = position.x;
}

void Enemy::handleVerticalMove(float deltaTime, const Map& map)
{
	if (isDefeat) return;
	
	velocity.y += gravity * deltaTime;

	sf::Vector2f newPosition = position;
	newPosition.y += velocity.y * deltaTime;

	collisionBox.left = position.x;
	collisionBox.top = newPosition.y;

	if (!mapCollision(map)) position.y = newPosition.y;
	else
	{
		if (velocity.y > 0) { // Collision falling down
			position.y = std::floor(newPosition.y); // Align to the ground
		}
		velocity.y = 0; // Reset vertical velocity
	}
	collisionBox.left = position.x;
	collisionBox.top = position.y;
}

void Enemy::UpdateTextures(float deltaTime)
{
	if (isDefeat == false)
		sprite.setTexture(*runAnimation.update(deltaTime));
	else
	{
		sprite.setTexture(texture[0]);
		dieTime -= deltaTime * 1.0f;
	}
}

void Enemy::handleDefeat()
{
	isDefeat = true;
	sprite.setScale(1.0f / texture[0].getSize().x, 0.25f / texture[0].getSize().y);
	velocity.x = 0;
	velocity.y = 0;

	if (!score)
		score = new FloatingScore(100, position);
}

//void Enemy::handleTeamCollision(EnemyList enemies)
//{
//	for (int i = 0; i < enemies.getSize(); i++)
//	{
//		if (*this != enemies.getEnemy(i))
//		{
//			collisionBox.left = position.x;
//			collisionBox.top = position.y;
//			if (this->teamCollision(enemies.getEnemy(i)))
//				velocity = -velocity;
//		}
//	}
//}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (isDefeat == false)
		sprite.setPosition(position);
	else if (dieTime > 0)
		sprite.setPosition(position.x, position.y + 0.75f);

	window.draw(sprite);

	// Draw score get
	if (score)
		score->Draw(window);
}

bool Enemy::mapCollision(const Map& map)
{
	for (int i = 0; i < map.collisionBoxList.size(); i++)
	{
		for (int j = 0; j < map.collisionBoxList[i].size(); j++)
		{
			if (collisionBox.intersects(map.collisionBoxList[i][j]) && (map.grid[i][j] == 1 || map.grid[i][j] == 2 || map.grid[i][j] == 4 || map.grid[i][j] == 3))
				return true;
		}
	}
	return false; // No collision
}

bool Enemy::teamCollision(const Enemy& other)
{
	return (collisionBox.intersects(other.collisionBox) && other.isDefeat == false);
}

bool Enemy::getDieStatus()
{
	return isDefeat;
}

float Enemy::getDieTime()
{
	return dieTime;
}

sf::Vector2f Enemy::getPosition()
{
	return position;
}

void Enemy::setPosition(const sf::Vector2f& position)
{
	this->position = position;
}

sf::FloatRect& Enemy::getCollisionBox()
{
	return collisionBox;
}

bool Enemy::operator!=(const Enemy& other)
{
	return (collisionBox.getPosition() != other.collisionBox.getPosition() && position != other.position);
}
