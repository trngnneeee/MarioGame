#include "Enemy.h"

Enemy::Enemy()
	: runAnimation(0.2f), gravity(5.0f), velocity(sf::Vector2f(3.0f, 0.0f)), isDead(false), dieTime(3.0f)
{
}

void Enemy::Begin()
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

void Enemy::Update(float deltaTime, const Map& map)
{
	// Update texture
	sprite.setTexture(*runAnimation.update(deltaTime));
	// Update collision
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	// Handle Move
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);
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
	for (int i = 0; i < map.getCollisionBoxList().size(); i++)
	{
		for (int j = 0; j < map.getCollisionBoxList()[i].size(); j++)
		{
			if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) && (grid[i][j] == 1 || grid[i][j] == 2 || grid[i][j] == 4 || grid[i][j] == 3))
				return true;
		}
	}
	return false; // No collision
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
