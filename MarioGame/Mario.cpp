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

	// Init small texture
	if (!textures[0].loadFromFile("./resources/textures/Mario/marioSmallRun1.png"))
		return;
	if (!textures[1].loadFromFile("./resources/textures/Mario/marioSmallRun2.png"))
		return;
	if (!textures[2].loadFromFile("./resources/textures/Mario/marioSmallRun3.png"))
		return;
	if (!textures[3].loadFromFile("./resources/textures/Mario/marioSmall.png"))
		return;
	if (!textures[4].loadFromFile("./resources/textures/Mario/marioSmallJump.png"))
		return;
	if (!deadTexture.loadFromFile("./resources/textures/Mario/marioDie.png"))
		return;

	// Init big texture
	if (!bigTexture[0].loadFromFile("./resources/textures/Mario/marioBigRun1.png"))
		return;
	if (!bigTexture[1].loadFromFile("./resources/textures/Mario/marioBigRun2.png"))
		return;
	if (!bigTexture[2].loadFromFile("./resources/textures/Mario/marioBigRun3.png"))
		return;
	if (!bigTexture[3].loadFromFile("./resources/textures/Mario/marioBig.png"))
		return;
	if (!bigTexture[4].loadFromFile("./resources/textures/Mario/marioBigJump.png"))

	runAnimation.addFrame(Frame(&textures[0], 0.08f));
	runAnimation.addFrame(Frame(&textures[1], 0.16f));
	runAnimation.addFrame(Frame(&textures[2], 0.24f));

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

void Mario::HandleMove(float deltaTime, Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars)
{	
	// Update previous position
	previousPos = position; 

	// Update position of collision box
	if (!levelUp)
		collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	else
		collisionBox = sf::FloatRect(position.x, position.y, bigSprite.getGlobalBounds().width, bigSprite.getGlobalBounds().height);

	// Jumping
	if (isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y = -jumpStrength;
		isOnGround = false;
		SoundManager::getInstance().playSound("jump");
	}

	// Vertical move
	HandleVerticalMove(deltaTime, map, mushrooms, stars);

	// Horizontal move
	HandleHorizontalMove(deltaTime, map, mushrooms, stars);
}

void Mario::HandleHorizontalMove(float deltaTime, Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars)
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

void Mario::HandleVerticalMove(float deltaTime, Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars)
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

void Mario::Update(float deltaTime, Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars)
{
	if (isDead)
	{  
		position.y -= v * deltaTime;
		v += tmpGravity * deltaTime;
		sprite.setTexture(deadTexture);
		deadTimer -= deltaTime;
		return;
	}

	if (outOfMapCollision())
	{
		isDead = true;
		return;
	}

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
	// Taking star
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

	// 10 coin -> 1 life
	if (coin >= 10)
	{
		coin -= 10;
		life++;
	}

	jumpStrength = (levelUp) ? 25.0f : 20.0f;

	HandleMove(deltaTime, map, mushrooms, stars);

	// Update animation
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

bool Mario::mapCollision(Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars)
{
	const std::vector<std::vector<int>>& grid = map.getGrid();
	const auto& collisionBoxes = map.getCollisionBoxList();

	// Define specific grid value sets for easier condition checks
	const std::set<int> solidBlocks = { 1, 2, 5, 11, 12, 13, 14, 24, 25, 26 };
	const int brickBlock = 3;
	const int hiddenMushroomBox = 4;

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
					std::srand(static_cast<unsigned>(std::time(0)));
					int randomNumber = 1 + (std::rand() % 2);

					if (randomNumber == 1)
					{
						auto newMushroom = std::make_unique<PowerUpMushroom>();
						newMushroom->Begin(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
						mushrooms.push_back(std::move(newMushroom));
					}
					else if (randomNumber == 2)
					{
						auto newStar = std::make_unique<InvicibleStar>();
						newStar->Begin(sf::Vector2f(i * map.getCellSize(), j * map.getCellSize()));
						stars.push_back(std::move(newStar));
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

void Mario::ResetStillLife()
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
