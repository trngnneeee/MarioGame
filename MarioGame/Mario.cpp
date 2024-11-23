#include "Mario.h"
#include "Map.h"
#include <iostream>


Mario::Mario()
	: runAnimation(0.3f), points(0), movementSpeed(7.0f), velocity(sf::Vector2f(0.0f, 0.0f)), jumpStrength(20.0f), gravity(40.0f), isDead(false), deadTimer(1.0f), life(3)
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
	if (!deadTexture.loadFromFile("./resources/textures/dead.png"))
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
		0.8f / textures[3].getSize().x,
		0.8f / textures[3].getSize().y
	);
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
		position.y += 8.0f * deltaTime;
		deadTimer -= deltaTime;
	}
}

void Mario::Update(float deltaTime, Map& map, EnemyList enemies, bool& gameOverFlag, sf::Music& music)
{
	if (isDead)
	{
		HandleDead(deltaTime);
		if (this->outOfMapCollision())
		{
			life--;
			gameOverFlag = true;
			return;
		}
	}

	HandleMove(deltaTime, map);

	for (int i = 0; i < enemies.getSize(); i++)
	{
		if (isDead == false && this->enemyCollison(enemies.getEnemy(i)))
		{
			music.stop();
			position.y -= 2.0f;
			isDead = true;
			return;
		}
	}

	if (this->outOfMapCollision()) gameOverFlag = true;

	// Update animation
	if (!isOnGround)
		sprite.setTexture(textures[4]);
	else if (velocity.x != 0)
		sprite.setTexture(*runAnimation.update(deltaTime));
	else if (isDead == true)
		sprite.setTexture(deadTexture);
	else sprite.setTexture(textures[3]);
}

void Mario::updateFlip()
{
	if (facingRight)
		sprite.setOrigin(0, 0);  // Left-center for right-facing
	else
		sprite.setOrigin(textures[3].getSize().x, 0); // Right-center for left-facing
	sprite.setScale(sf::Vector2f(0.8f / textures[3].getSize().x * (facingRight ? 1 : -1), 0.8f / textures[3].getSize().y));
}

void Mario::Draw(sf::RenderWindow& window)
{
	updateFlip();
	sprite.setPosition(position);
	window.draw(sprite);
}

bool Mario::mapCollision(Map& map)
{
	std::vector<std::vector<int>> grid = map.getGrid();

	for (int i = 0; i < map.getCollisionBoxList().size(); i++)
	{
		for (int j = 0; j < map.getCollisionBoxList()[i].size(); j++)
		{
			if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) && (grid[i][j] == 1 || grid[i][j] == 2 || grid[i][j] == 4))
				return true;
			else if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) && (grid[i][j] == 3))
			{
				if (velocity.y < 0 && collisionBox.top <= map.getCollisionBoxList()[i][j].top + map.getCollisionBoxList()[i][j].height && collisionBox.top >= map.getCollisionBoxList()[i][j].top)
				{
					points += 50;
					map.handleBrickCollision(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
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
	return (position.y > 16.0f);
}

void Mario::setPoints(const int& n)
{
	points = n;
}
void Mario::setCoins(const int& n)
{
	coins = n;
}


int Mario::getLife()
{
	return life;
}

void Mario::setLife(const int& n)
{
	life = n;
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
	isDead = false;
	deadTimer = 3.0f;
	isOnGround = true;
}

int& Mario::getPoints()
{
	return points;
}
int& Mario::getCoins()
{
	return coins;
}

sf::Vector2f Mario::getPosition()
{
	return position;
}
sf::FloatRect Mario::getCollisionBox() const
{
	return collisionBox;
}
