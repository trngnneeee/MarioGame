#include "Mario.h"
#include "Map.h"
#include <iostream>


Mario::Mario()
	: runAnimation(0.3f), points(0), movementSpeed(10.0f), velocity(sf::Vector2f(0.0f, 0.0f)), jumpStrength(20.0f), gravity(40.0f), isDead(false)
{
}

// Functions
void Mario::Begin(const sf::Vector2f& marioPosition)
{	
	// Init start position for mario
	position = marioPosition;

	// Init texture
	if (!textures[0].loadFromFile("./resources/textures/run1.png"))
		return;
	if (!textures[1].loadFromFile("./resources/textures/run2.png"))
		return;
	if (!textures[2].loadFromFile("./resources/textures/run3.png"))
		return;
	if (!textures[3].loadFromFile("./resources/textures/mario.png"))
		return;
	if (!textures[4].loadFromFile("./resources/textures/jump.png"))
		return;
	runAnimation.addFrame(Frame(&textures[0], 0.1f));
	runAnimation.addFrame(Frame(&textures[1], 0.2f));
	runAnimation.addFrame(Frame(&textures[2], 0.3f));

	// Init jump sound
	if (!jumpEffect.openFromFile("./resources/soundEffect/jump.wav"))
		return;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,       
		1.0f / textures[3].getSize().x,
		1.9f / textures[3].getSize().y
	);

	// Init dead sound effect
	deadEffect.openFromFile("./resources/soundEffect/dead.mp3");
}

void Mario::HandleMove(float deltaTime, Map& map)
{
	// Update previous position
	previousPos = position;

	// Update position of collision box
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	// Horizontal move
	HandleHorizontalMove(deltaTime, map);

	// Jumping
	if (isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y = -jumpStrength;
		isOnGround = false;
		jumpEffect.play();
	}

	// Vertical move
	HandleVerticalMove(deltaTime, map);
}

void Mario::HandleHorizontalMove(float deltaTime, Map& map)
{
	// Horizontal move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Vector2f newPosition = position;
		newPosition.x += movementSpeed * deltaTime;
		collisionBox.left = newPosition.x;
		collisionBox.top = position.y;
		if (!mapCollision(map)) position.x = newPosition.x;
		facingRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Vector2f newPosition = position;
		newPosition.x -= movementSpeed * deltaTime;
		collisionBox.left = newPosition.x;
		collisionBox.top = position.y;
		if (!mapCollision(map)) position.x = newPosition.x;
		facingRight = false;
	}

	// Calculate horizontal velocity
	velocity.x = (position.x - previousPos.x) / deltaTime;
}

void Mario::HandleVerticalMove(float deltaTime, Map& map)
{
	// Applying gravity
	velocity.y += gravity * deltaTime;
	sf::Vector2f newPosition = position;
	newPosition.y += velocity.y * deltaTime;
	collisionBox.left = position.x;
	collisionBox.top = newPosition.y;

	// Vertical collision check
	if (!mapCollision(map))
	{
		position.y = newPosition.y;
	}
	else {
		if (velocity.y > 0) {
			position.y = newPosition.y - velocity.y * deltaTime;
			velocity.y = 0;
			isOnGround = true;
		}
		else if (velocity.y < 0) {
			position.y = newPosition.y - velocity.y * deltaTime;
			velocity.y = 0;
		}
	}
}

void Mario::HandleDead(float deltaTime)
{
	if (deadTimer > 0)
	{
		position.y += 10.0f * deltaTime;
		deadTimer -= deltaTime;
	}
}

void Mario::Update(float deltaTime, Map& map, EnemyList enemies, bool& gameOverFlag)
{
	if (isDead)
	{
		deadEffect.play();
		HandleDead(deltaTime); 
		if (this->outOfMapCollision())
		{
			gameOverFlag = true;
			return;
		}
	}

	HandleMove(deltaTime, map);

	for (int i = 0; i < enemies.getSize(); i++)
	{
		if (this->enemyCollison(enemies.getEnemy(i)))
			isDead = true;
	}

	if (this->outOfMapCollision()) gameOverFlag = true;

	// Update animation
	if (!isOnGround)
		sprite.setTexture(textures[4]);
	else if (velocity.x != 0)
		sprite.setTexture(*runAnimation.update(deltaTime));
	else sprite.setTexture(textures[3]);
}

void Mario::updateFlip()
{
	if (facingRight)
		sprite.setOrigin(0, 0);  // Left-center for right-facing
	else
		sprite.setOrigin(textures[3].getSize().x, 0); // Right-center for left-facing
	sprite.setScale(sf::Vector2f(0.7f / textures[3].getSize().x * (facingRight ? 1 : -1), 1.9f / textures[3].getSize().y));
}

void Mario::Draw(sf::RenderWindow& window)
{
	updateFlip();
	sprite.setPosition(position);
	window.draw(sprite);
}

bool Mario::mapCollision(Map& map)
{
	for (int i = 0; i < map.collisionBoxList.size(); i++)
	{
		for (int j = 0; j < map.collisionBoxList[i].size(); j++)
		{
			if (collisionBox.intersects(map.collisionBoxList[i][j]) && (map.grid[i][j] == 1 || map.grid[i][j] == 2 || map.grid[i][j] == 4))
				return true;
			else if (collisionBox.intersects(map.collisionBoxList[i][j]) && (map.grid[i][j] == 3))
			{
				if (velocity.y < 0)
				{
					points += 50;
					map.Update(sf::Vector2f(i * map.cellSize, j * map.cellSize));
					return true;
				}
				else return true;
			}
		}
	}
	return false; 
}

bool Mario::enemyCollison(Enemy& enemy)
{	 
	if (enemy.getCollisionBox().intersects(collisionBox) && enemy.getDieStatus() == false)
	{
		if (velocity.y > 0 && position.y + collisionBox.height <= enemy.getPosition().y + enemy.getCollisionBox().height / 2)
		{
			points += 100;
			velocity.y = -jumpStrength / 2; // Bounce Mario up slightly
			enemy.handleDefeat();
			return false;
		}
		else return true;
	}
	return false;
}

bool Mario::outOfMapCollision()
{
	return (position.y >= 18.0f);
}

void Mario::Reset()
{
	position = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0.0f, 0.0f);
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[3].getSize().x,
		1.9f / textures[3].getSize().y
	);
	runAnimation.Reset();
	points = 0;
	isDead = false;
}

int Mario::getPoints()
{
	return points;
}

sf::Vector2f Mario::getPosition()
{
	return position;
}