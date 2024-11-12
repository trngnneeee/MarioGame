#include "Enemy.h"

Enemy::Enemy()
	:runAnimation(0.2f), velocity(3.0f)
{	
}

void Enemy::Begin()
{
	// Load texture
	if (!texture[0].loadFromFile("./resources/textures/enemy1.png"))
		return;
	if (!texture[1].loadFromFile("./resources/textures/enemy2.png"))
		return;

	runAnimation.addFrame(Frame(&texture[0], 0.1f));
	runAnimation.addFrame(Frame(&texture[1], 0.2f));

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / texture[0].getSize().x,
		1.0f / texture[0].getSize().y
	);
}

void Enemy::Update(float deltaTime, const Map& map)
{
	// Check Collision
	float newPosition = position.x - velocity * deltaTime;
	collisionBox.left = newPosition;
	collisionBox.top = position.y;
	if (!mapCollision(map)) {
		position.x = newPosition;
	}
	else velocity = -velocity;

	sprite.setTexture(*runAnimation.update(deltaTime));
}

void Enemy::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(1.0f / texture[0].getSize().x, 1.0f / texture[0].getSize().y));
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
