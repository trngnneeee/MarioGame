#include "Enemy.h"

Enemy::Enemy()
	: runAnimation(0.2f), gravity(50.0f), velocity(sf::Vector2f(3.0f, 0.0f)), isDead(false), dieTime(3.0f), v(10.0f), tmpGravity(-30.0f), inGame(false)
{
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

void Enemy::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
	if (score)
		score->Draw(window);
}

bool Enemy::mapCollision(const Map& map)
{
	std::vector<std::vector<int>> grid = map.getGrid();
	const std::set<int> excludedTiles = { 23, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };

	for (int i = 0; i < map.getCollisionBoxList().size(); i++)
	{
		for (int j = 0; j < map.getCollisionBoxList()[i].size(); j++)
		{
			if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) &&
				excludedTiles.find(grid[i][j]) == excludedTiles.end())
			{
				return true;
			}
		}
	}
	return false;
}

void Enemy::Reset()
{
	runAnimation.Reset();
	textures.clear();
	if (score) delete score;
}

// Setter/Getter
sf::FloatRect Enemy::getCollisionBox() const
{
	return collisionBox;
}

bool Enemy::getDieStatus() const
{
	return isDead;
}

void Enemy::setDieStatus(const bool& value)
{
	isDead = value;
}

sf::Vector2f Enemy::getPosition() const
{
	return position;
}

float Enemy::getDieTime()
{
	return dieTime;
}

sf::Vector2f Enemy::getVelocity() const
{
	return velocity;
}

void Enemy::setVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

bool Enemy::getGameState()
{
	return inGame;
}

void Enemy::setGameState(const bool& value)
{
	inGame = value;
}


