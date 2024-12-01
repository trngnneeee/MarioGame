#include "Mario.h"
#include "Map.h"

Mario::Mario()
	: runAnimation(0.24f), bigRunAnimation(0.3f), points(0), movementSpeed(7.0f), velocity(sf::Vector2f(0.0f, 0.0f)), jumpStrength(20.0f), gravity(40.0f), isDead(false), life(3), deadTimer(3.0f), v(10.0f), tmpGravity(-30.0f), koopaKickSpeed(20.0f), levelUp(false), invicibleTime(0.0f), invicibleTime2(0.0f), coin(0), mapArchive(1)
{
}

// Functions
void Mario::Begin(const sf::Vector2f& marioPosition)
{	
	// Init start position for mario
	startPosition = marioPosition;
	position = marioPosition;

	deadTexture.loadFromFile("./resources/textures/Mario/marioDie.png");

	// Init small texture
	std::vector<std::string> filePath1 = {
		"marioSmallRun1.png",
		"marioSmallRun2.png",
		"marioSmallRun3.png",
		"marioSmall.png",
		"marioSmallJump.png",
	};
	for (int i = 0; i < filePath1.size(); i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Mario/" + filePath1[i]);
		textures.push_back(tmp);
	}
	runAnimation.addFrame(Frame(&textures[0], 0.08f));
	runAnimation.addFrame(Frame(&textures[1], 0.16f));
	runAnimation.addFrame(Frame(&textures[2], 0.24f));


	// Init big texture
	std::vector<std::string> filePath2 = {
		"marioBigRun1.png",
		"marioBigRun2.png",
		"marioBigRun3.png",
		"marioBig.png",
		"marioBigJump.png",
	};
	for (int i = 0; i < filePath1.size(); i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Mario/" + filePath1[i]);
		bigTexture.push_back(tmp);
	}

	bigRunAnimation.addFrame(Frame(&bigTexture[0], 0.1f));
	bigRunAnimation.addFrame(Frame(&bigTexture[1], 0.2f));
	bigRunAnimation.addFrame(Frame(&bigTexture[2], 0.3f));

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,       
		0.8f / textures[3].getSize().x,
		0.8f / textures[3].getSize().y
	);
}

void Mario::Update(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars)
{
	if (handleDead(deltaTime)) return;
	if (handleOutOfMap()) return;
	handleBlinkEffect(deltaTime);
	handleCollectCoin();
	handleJumpStrength();
	HandleMove(deltaTime, map, mushrooms, stars);
	UpdateTexture(deltaTime);
}

void Mario::Draw(sf::RenderWindow& window)
{
	updateFlip();
	if (!levelUp || isDead)
	{
		sprite.setPosition(position);
		window.draw(sprite);
	}
	else
	{
		bigSprite.setPosition(position);
		window.draw(bigSprite);
	}
}

void Mario::HandleMove(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars)
{	
	// Update previous position
	previousPos = position; 
	UpdateCollisionBox();
	handleJump(deltaTime);
	handleVerticalMove(deltaTime, map, mushrooms, stars);
	handleHorizontalMove(deltaTime, map, mushrooms, stars);
}

void Mario::UpdateCollisionBox()
{
	if (!levelUp)
		collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	else
		collisionBox = sf::FloatRect(position.x, position.y, bigSprite.getGlobalBounds().width, bigSprite.getGlobalBounds().height);
}

void Mario::handleJump(float deltaTime)
{
	if (isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y = -jumpStrength;
		isOnGround = false;
		SoundManager::getInstance().playSound("jump");
	}
}

void Mario::handleHorizontalMove(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars)
{
	// Horizontal move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Vector2f newPosition = position;
		newPosition.x += movementSpeed * deltaTime;
		collisionBox.left = newPosition.x;
		collisionBox.top = position.y;
		if (!mapCollision(map, mushrooms, stars)) position.x = newPosition.x;
		facingRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Vector2f newPosition = position;
		newPosition.x -= movementSpeed * deltaTime;
		collisionBox.left = newPosition.x;
		collisionBox.top = position.y;
		if (!mapCollision(map, mushrooms, stars)) position.x = newPosition.x;
		facingRight = false;
	}

	// Calculate horizontal velocity
	velocity.x = (position.x - previousPos.x) / deltaTime;
}

void Mario::handleVerticalMove(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars)
{
	// Applying gravity
	velocity.y += gravity * deltaTime;
	sf::Vector2f newPosition = position;
	newPosition.y += velocity.y * deltaTime;
	collisionBox.left = position.x;
	collisionBox.top = newPosition.y;

	// Vertical collision check
	if (!mapCollision(map, mushrooms, stars))
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

bool Mario::handleDead(float deltaTime)
{
	if (isDead)
	{
		position.y -= v * deltaTime;
		v += tmpGravity * deltaTime;
		sprite.setTexture(deadTexture);
		deadTimer -= deltaTime;
		return true;
	}
	return false;
}

bool Mario::handleOutOfMap()
{
	if (outOfMapCollision())
	{
		isDead = true;
		return true;
	}
	return false;
}

void Mario::handleBlinkEffect(float deltaTime)
{
	// Shrinking from Big size to Small size
	if (invicibleTime > 0)
	{
		invicibleTime -= deltaTime;
		float alpha = (sin(invicibleTime * 100.0f) * 0.5f + 0.5f) * 255;
		if (!levelUp)
			sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		else
			bigSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
	}
	// Taking invicible star
	else if (invicibleTime2 > 0)
	{
		invicibleTime2 -= deltaTime;
		float alpha = (sin(invicibleTime2 * 100.0f) * 0.5f + 0.5f) * 255;
		if (!levelUp)
			sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		else
			bigSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
		bigSprite.setColor(sf::Color(255, 255, 255, 255));
	}
}

void Mario::handleCollectCoin()
{
	if (coin >= 10)
	{
		coin -= 10;
		life++;
	}
}

void Mario::handleJumpStrength()
{
	jumpStrength = (levelUp) ? 25.0f : 20.0f;
}

void Mario::UpdateTexture(float deltaTime)
{
	if (!levelUp)
	{
		if (!isOnGround)
			sprite.setTexture(textures[4]);
		else if (velocity.x != 0)
			sprite.setTexture(*runAnimation.update(deltaTime));
		else if (isDead == true)
			sprite.setTexture(deadTexture);
		else sprite.setTexture(textures[3]);
	}
	else
	{
		if (!isOnGround)
			bigSprite.setTexture(bigTexture[4]);
		else if (velocity.x != 0)
			bigSprite.setTexture(*bigRunAnimation.update(deltaTime));
		else if (isDead == true)
			bigSprite.setTexture(deadTexture);
		else bigSprite.setTexture(bigTexture[3]);
	}
}

void Mario::updateFlip()
{
	if (!levelUp)
	{
		sprite.setScale(sf::Vector2f(0.8f / textures[3].getSize().x * (facingRight ? 1 : -1), 0.8f / textures[3].getSize().y));
		if (facingRight)
			sprite.setOrigin(0, 0);  // Left-center for right-facing
		else
			sprite.setOrigin(textures[3].getSize().x, 0); // Right-center for left-facing
	}
	else
	{
		bigSprite.setScale(sf::Vector2f(0.8f / bigTexture[3].getSize().x * (facingRight ? 1 : -1), 1.0f / bigTexture[3].getSize().y));
		if (facingRight)
			bigSprite.setOrigin(0, 0);  // Left-center for right-facing
		else
			bigSprite.setOrigin(bigTexture[3].getSize().x, 0); // Right-center for left-facing
	}
}

bool Mario::mapCollision(Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars)
{
	const std::vector<std::vector<int>>& grid = map.getGrid();
	const auto& collisionBoxes = map.getCollisionBoxList();

	const std::set<int> solidBlocks = { 1, 2, 5, 11, 12, 13, 14, 24, 25, 26 };
	const int brickBlock = 3;
	const int hiddenMushroomBox = 4;

	HiddenBoxItemFactory factory;

	for (size_t i = 0; i < collisionBoxes.size(); i++)
	{
		for (size_t j = 0; j < collisionBoxes[i].size(); j++)
		{
			const sf::FloatRect& currentBox = collisionBoxes[i][j];
			int tileType = grid[i][j];

			// Check collision with solid blocks
			if (collisionBox.intersects(currentBox) && solidBlocks.count(tileType))
			{
				return true;
			}
			// Handle brick block collisions
			else if (collisionBox.intersects(currentBox) && tileType == brickBlock)
			{
				if (velocity.y < 0 && collisionBox.top <= currentBox.top + currentBox.height && collisionBox.top >= currentBox.top)
				{
					if (levelUp)
					{
						SoundManager::getInstance().playSound("brick");
						points += 50;
						map.handleBrickCollision(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
					}
					return true;
				}
				else
				{
					return true;
				}
			}
			// Handle hidden box collisions (mushroom or star)
			else if (collisionBox.intersects(currentBox) && tileType == hiddenMushroomBox)
			{
				if (velocity.y < 0 && collisionBox.top <= currentBox.top + currentBox.height && collisionBox.top >= currentBox.top)
				{
					// Generate random number (1 or 2) to spawn power-up
					SoundManager::getInstance().playSound("item");
					std::srand(static_cast<unsigned>(std::time(0)));
					int randomNumber = 1 + (std::rand() % 2);

					if (randomNumber == 1)
					{
						HiddenBoxItem* newItem = factory.createItem("Mushroom");
						if (newItem)
						{
							newItem->Begin(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
							mushrooms.push_back(static_cast<PowerUpMushroom*>(newItem));
						}
					}
					else if (randomNumber == 2)
					{
						HiddenBoxItem* newItem = factory.createItem("Star");
						if (newItem)
						{
							newItem->Begin(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
							stars.push_back(static_cast<InvicibleStar*>(newItem));
						}
					}

					map.handleHiddenBoxCollision(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
					return true;
				}
				else
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Mario::outOfMapCollision()
{
	return (position.y > 16.0f);
}

bool Mario::goombasCollision(Goombas& goombas) {
	if (goombas.getCollisionBox().intersects(collisionBox) && goombas.getDieStatus() == false)
	{
		if (velocity.y > 0 && position.y + collisionBox.height <= goombas.getPosition().y + goombas.getCollisionBox().height / 2)
		{
			points += 100;
			velocity.y = -jumpStrength / 2; 
			goombas.setDieStatus(true);
			SoundManager::getInstance().playSound("goomba");
			return false;
		}
		else return true;
	}
	return false;
}

bool Mario::koopaCollision(Koopa& koopa)
{
	if (koopa.getCollisionBox().intersects(collisionBox) && koopa.getDieStatus() == false)
	{
		if (velocity.y > 0 && position.y + collisionBox.height <= koopa.getPosition().y + koopa.getCollisionBox().height / 2)
		{
			if (koopa.getInShellStatus() == false)
			{
				SoundManager::getInstance().playSound("goomba");
				velocity.y = -jumpStrength / 2;
				koopa.setInShellStatus(true);
			}
			else
			{
				velocity.y = -jumpStrength / 2;
				koopa.setStandTimer(3.0f);
			}
			koopa.setVelocity(sf::Vector2f(0.0f, 0.0f));
			return false;
		}
		else
		{
			if (koopa.getInShellStatus() == false) return true;
			else
			{
				int kickDirection = (!facingRight) ? 1 : -1;
				koopa.setVelocity(sf::Vector2f(koopaKickSpeed * kickDirection, 0));
				SoundManager::getInstance().playSound("kick");
				return false;
			}
		}
	}
	return false;
}

bool Mario::mushroomCollision(PowerUpMushroom& mushroom)
{
	return collisionBox.intersects(mushroom.getCollisionBox());
}

bool Mario::starCollision(InvicibleStar& star)
{
	return collisionBox.intersects(star.getCollisionBox());
}

bool Mario::coinCollision(Coin& coin)
{
	return collisionBox.intersects(coin.getCollisionBox());
}

float Mario::distanceX(const Enemy& enemy)
{
	return std::abs(position.x - enemy.getPosition().x);
}

void Mario::Reset()
{
	runAnimation = 0.24f;
	bigRunAnimation = 0.3f;
	points = 0;
	movementSpeed = 7.0f;
	jumpStrength = 20.0f;
	gravity = 40.0f;
	isDead = false;
	life = 3;
	deadTimer = 3.0f;
	v = 10.0f;
	tmpGravity = -30.0f;
	koopaKickSpeed = 20.0f;
	levelUp = false;
	invicibleTime = 0.0f;
	invicibleTime2 = 0.0f;
	coin = 0;
	mapArchive = 1;

	position = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0.0f, 0.0f);
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[3].getSize().x,
		1.9f / textures[3].getSize().y
	);
	runAnimation.Reset();
}

void Mario::ResetAfterDead()
{
	isDead = false;
	life--;
	deadTimer = 3.0f;
	levelUp = false;
	invicibleTime = 1.5f;
	position = startPosition;
	v = 10.0f;
	tmpGravity = -30.0f;
}

void Mario::ResetAfterWin()
{
	runAnimation = 0.24f;
	bigRunAnimation = 0.3f;
	movementSpeed = 7.0f;
	jumpStrength = 20.0f;
	gravity = 40.0f;
	isDead = false;
	deadTimer = 3.0f;
	v = 10.0f;
	tmpGravity = -30.0f;
	koopaKickSpeed = 20.0f;
	levelUp = false;
	invicibleTime = 0.0f;
	invicibleTime2 = 0.0f;

	position = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0.0f, 0.0f);
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[3].getSize().x,
		1.9f / textures[3].getSize().y
	);
	runAnimation.Reset();
}

// Getter/Setter
int Mario::getPoints()
{
	return points;
}

void Mario::setPoints(const int& n)
{
	points = n;
}

bool Mario::getDeadStatus()
{
	return isDead;
}

void Mario::setDeadStatus(const bool& value) {
	isDead = value;
}

float Mario::getDeadTimer()
{
	return deadTimer;
}

sf::FloatRect Mario::getCollisionBox() const
{
	return collisionBox;
}

sf::Vector2f Mario::getPosition()
{
	return position;
}

sf::Vector2f Mario::getStartPosition()
{
	return startPosition;
}

void Mario::setPosition(sf::Vector2f position)
{
	this->position = position;
}

int Mario::getLife()
{
	return life;
}

void Mario::setLife(const int& n)
{
	life = n;
}

sf::Vector2f Mario::getVelocity()
{
	return velocity;
}

bool Mario::getLevelUpStatus()
{
	return levelUp;
}

void Mario::setLevelUpStatus(const bool& value)
{
	levelUp = value;
}

float Mario::getInvicibleTime()
{
	return invicibleTime;
}

void Mario::setInvicibleTime(const float& time) 
{
	invicibleTime = time;
}

float Mario::getInvicibleTime2()
{
	return invicibleTime2;
}

void Mario::setInvicibleTime2(const float& time)
{

	invicibleTime2 = time;
}

int Mario::getCoin()
{
	return coin;
}

void Mario::setCoin(const int coin)
{
	this->coin = coin;
}

int Mario::getMapArchive()
{
	return mapArchive;
}

void Mario::setMapArchive(const int& value)
{
	mapArchive = value;
}
