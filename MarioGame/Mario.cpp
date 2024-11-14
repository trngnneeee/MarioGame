#include "Mario.h"
#include "Map.h"
#include <iostream>


Mario::Mario()
	: runAnimation(0.3f), points(0), movementSpeed(10.0f), velocity(sf::Vector2f(0.0f, 0.0f)), jumpStrength(18.0f), gravity(40.0f)
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
}

void Mario::HandleMove(float deltaTime, const Map& map)
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

void Mario::HandleHorizontalMove(float deltaTime, const Map& map)
{
	// Update position of collision box
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

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

void Mario::HandleVerticalMove(float deltaTime, const Map& map)
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

void Mario::Update(float deltaTime, const Map& map, EnemyList enemies, bool& isDead)
{
	HandleMove(deltaTime, map);

	for (int i = 0; i < enemies.getSize(); i++)
	{
		if (this->enemyCollison(enemies.getEnemy(i))) isDead = true;
	}

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

bool Mario::mapCollision(Map map)
{
	for (int i = 0; i < map.collisionBoxList.size(); i++)
	{
		for (int j = 0; j < map.collisionBoxList[i].size(); j++)
		{
			if (collisionBox.intersects(map.collisionBoxList[i][j]) && (map.grid[i][j] == 1 || map.grid[i][j] == 2 || map.grid[i][j] == 4 || map.grid[i][j] == 3))
				return true;
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
			enemy.handleDefeat();// Mark enemy as defeated
			return false;
		}
		else return true;
	}
	return false;
}

bool Mario::outOfMapCollision()
{
	if (position.y >= 17.0f) return true;
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
}

int Mario::getPoints()
{
	return points;
}

sf::Vector2f Mario::getPosition()
{
	return position;
}