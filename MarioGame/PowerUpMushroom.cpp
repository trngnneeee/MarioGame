#include "PowerUpMushroom.h"
#include "Map.h"

PowerUpMushroom::PowerUpMushroom()
	: gravity(50.0f), velocity(sf::Vector2f(5.0f, 0.0f)), isOut(false), isDead(false), dieTime(1.0f), animation(0.2)
{
}

void PowerUpMushroom::Begin(sf::Vector2f mushroomPosition)
{
	// Init texture
	for (int i = 0; i < 2; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Mushroom/mushroom" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 2; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	sprite.setScale(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y);

	// Init position
	position = mushroomPosition;
	hiddenBoxPosition = mushroomPosition.y;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);
}

void PowerUpMushroom::handleHorizontalMove(float deltaTime, const Map& map)
{
	sf::Vector2f newPosition = position;
	newPosition.x += velocity.x * deltaTime;

	collisionBox.left = newPosition.x;
	collisionBox.top = position.y;

	if (!mapCollision(map))
		position.x = newPosition.x;
	else
		velocity.x = -velocity.x;
	collisionBox.left = position.x;
}

void PowerUpMushroom::handleVerticalMove(float deltaTime, const Map& map)
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

void PowerUpMushroom::Update(float deltaTime, const Map& map)
{
	if (!isOut)
	{
		sprite.setTexture(textures[0]);
		if (position.y > hiddenBoxPosition - 1.0f)
			position.y -= 1.0f * deltaTime;
		else
			isOut = true;
		return;
	}

	if (isDead)
	{
		sprite.setColor(sf::Color(255, 255, 255, 0));
		velocity = sf::Vector2f(0.0f, 0.0f);
		if (dieTime > 0)
		{
			dieTime -= deltaTime;
			if (!score)
				score = new FloatingScore(1000, position);
			else score->Update(deltaTime);
		}
		else
			if (score) delete score;
		return;
	}

	// Update collision
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	// Handle Move
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);

	sprite.setTexture(*animation.update(deltaTime));
}

void PowerUpMushroom::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
	if (score)
		score->Draw(window);
}

bool PowerUpMushroom::mapCollision(const Map& map)
{
	std::vector<std::vector<int>> grid = map.getGrid();
	for (int i = 0; i < map.getCollisionBoxList().size(); i++)
	{
		for (int j = 0; j < map.getCollisionBoxList()[i].size(); j++)
		{
			if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) && grid[i][j] != 23)
			{
				return true;
			}
		}
	}
	return false;
}

sf::FloatRect PowerUpMushroom::getCollisionBox() const
{
	return collisionBox;
}

bool PowerUpMushroom::getDeadStatus()
{
	return isDead;
}

void PowerUpMushroom::setDeadStatus(const bool& value)
{
	isDead = value;
}

float PowerUpMushroom::getDieTime()
{
	return dieTime;
}

bool PowerUpMushroom::getOutStatus()
{
	return isOut;
}
