#include "HiddenBoxItem.h"
#include "Map.h"

HiddenBoxItem::HiddenBoxItem()
	: gravity(50.0f), velocity(sf::Vector2f(5.0f, 0.0f)), isOut(false), isDead(false), dieTime(1.0f), animation(0.2)
{
}

void HiddenBoxItem::Update(float deltaTime, const Map& map)
{
	if (handleOut(deltaTime)) return;
	if (handleDead(deltaTime)) return;

	// Update collision
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);

	sprite.setTexture(*animation.update(deltaTime));
}

void HiddenBoxItem::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
	if (score)
		score->Draw(window);
}

void HiddenBoxItem::Reset()
{
	animation.Reset();
	textures.clear();
	if (score) delete score;
}

void HiddenBoxItem::handleHorizontalMove(float deltaTime, const Map& map)
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

void HiddenBoxItem::handleVerticalMove(float deltaTime, const Map& map)
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

bool HiddenBoxItem::handleOut(float deltaTime)
{
	if (!isOut)
	{
		sprite.setTexture(textures[0]);
		if (position.y > hiddenBoxPosition - 1.0f)
			position.y -= 1.0f * deltaTime;
		else
			isOut = true;
		return true;
	}
	return false;
}

bool HiddenBoxItem::handleDead(float deltaTime)
{
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
		return true;
	}
	return false;
}

bool HiddenBoxItem::mapCollision(const Map& map)
{
	std::vector<std::vector<int>> grid = map.getGrid();
	const std::set<int> excludedTiles = { 1, 2, 3, 4, 5, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 42, 44, 45, 46, 47 };

	for (int i = 0; i < map.getCollisionBoxList().size(); i++)
	{
		for (int j = 0; j < map.getCollisionBoxList()[i].size(); j++)
		{
			if (collisionBox.intersects(map.getCollisionBoxList()[i][j]) &&
				excludedTiles.find(grid[i][j]) != excludedTiles.end())
			{
				return true;
			}
		}
	}
	return false;
}

sf::FloatRect HiddenBoxItem::getCollisionBox() const
{
	return collisionBox;
}

bool HiddenBoxItem::getDeadStatus()
{
	return isDead;
}

void HiddenBoxItem::setDeadStatus(const bool& value)
{
	isDead = value;
}

float HiddenBoxItem::getDieTime()
{
	return dieTime;
}

bool HiddenBoxItem::getOutStatus()
{
	return isOut;
}

sf::Vector2f HiddenBoxItem::getPosition()
{
	return position;
}
