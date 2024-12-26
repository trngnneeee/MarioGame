#include "Mario.h"
#include "Map.h"

Mario::Mario()
	: runAnimation(0.24f), bigRunAnimation(0.3f), points(0), movementSpeed(7.0f), velocity(sf::Vector2f(0.0f, 0.0f)), jumpStrength(20.0f), gravity(60.0f), isDead(false), life(3), deadTimer(3.0f), v(10.0f), tmpGravity(-30.0f), koopaKickSpeed(20.0f), levelUp(false), invicibleTime(0.0f), invicibleTime2(0.0f), coin(0), mapArchive(1), shootCooldown(0.0f), shootCooldownTimer(0.2f), shootingAbility(false), smallSwimAnimation(0.5f), bigSwimAnimation(0.5f), outOfWaterTime(2.0f), isSwimming(false), isWinning(false), smallWinAnimation(0.2f), bigWinAnimation(0.2f)
{
}

// Functions
void Mario::Begin(const sf::Vector2f& marioPosition, const int& characterSelected)
{	
	// Select Character
	this->characterSelected = characterSelected;

	std::string texturePack = "";
	if (characterSelected == 0) texturePack = "Mario";
	else if (characterSelected == 1) texturePack = "Luigi";
	else if (characterSelected == 2) texturePack = "FireMario";

	// Init start position for mario
	startPosition = marioPosition;
	position = marioPosition;

	deadTexture.loadFromFile("./resources/textures/" + texturePack + "/marioDie.png");

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
		tmp.loadFromFile("./resources/textures/" + texturePack + "/" + filePath1[i]);
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
	for (int i = 0; i < filePath2.size(); i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/" + texturePack + "/" + filePath2[i]);
		bigTexture.push_back(tmp);
	}

	bigRunAnimation.addFrame(Frame(&bigTexture[0], 0.1f));
	bigRunAnimation.addFrame(Frame(&bigTexture[1], 0.2f));
	bigRunAnimation.addFrame(Frame(&bigTexture[2], 0.3f));

	// Swimming animation
	for (int i = 0; i < 5; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/" + texturePack + "/marioSmallSwim" + std::to_string(i + 1) + ".png");
		smallSwimTextures.push_back(tmp);
	}
	for (int i = 0; i < 5; i++)
	{
		smallSwimAnimation.addFrame(Frame(&smallSwimTextures[i], 0.1f * (i + 1)));
	}
	for (int i = 0; i < 5; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/" + texturePack + "/marioBigSwim" + std::to_string(i + 1) + ".png");
		bigSwimTextures.push_back(tmp);
	}
	for (int i = 0; i < 5; i++)
	{
		bigSwimAnimation.addFrame(Frame(&bigSwimTextures[i], 0.1f * (i + 1)));
	}

	// Win texture
	sf::Texture tmp;
	tmp.loadFromFile("./resources/textures/" + texturePack + "/marioSmallWin.png");
	winTextures.push_back(tmp);
	tmp.loadFromFile("./resources/textures/" + texturePack + "/marioSmallWin2.png");
	winTextures.push_back(tmp);
	tmp.loadFromFile("./resources/textures/" + texturePack + "/marioBigWin.png");
	winTextures.push_back(tmp);
	tmp.loadFromFile("./resources/textures/" + texturePack + "/marioBigWin2.png");
	winTextures.push_back(tmp);

	smallWinAnimation.addFrame(Frame(&winTextures[0], 0.1f));
	smallWinAnimation.addFrame(Frame(&winTextures[1], 0.2f));

	bigWinAnimation.addFrame(Frame(&winTextures[2], 0.1f));
	bigWinAnimation.addFrame(Frame(&winTextures[3], 0.2f));

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,       
		0.8f / textures[3].getSize().x,
		0.8f / textures[3].getSize().y
	);
}

void Mario::Update(float deltaTime, Map& map, const std::vector<FlyingBridge*>& bridges)
{
	if (!isWinning)
	{
		updateSwimmingState(deltaTime);
		if (handleDead(deltaTime)) return;
		if (handleOutOfMap()) return;
		handleBlinkEffect(deltaTime);
		handleCollectCoin();
		handleJumpStrength();
		HandleMove(deltaTime, map);
		HandleBridgeStanding(deltaTime ,bridges);
		UpdateTexture(deltaTime);
		// Shoot
		handleShoot(deltaTime);
		UpdateBullet(deltaTime, map);
	}
	else
	{
		position.y += 5.0f * deltaTime;
		sprite.setTexture(*smallWinAnimation.update(deltaTime));
		bigSprite.setTexture(*bigWinAnimation.update(deltaTime));
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
	DrawBullet(window);
}

void Mario::HandleMove(float deltaTime, Map& map)
{	
	// Update previous position
	previousPos = position; 
	UpdateCollisionBox();
	if (!isSwimming)
	{
		handleJump(deltaTime);
		handleVerticalMove(deltaTime, map);
		handleHorizontalMove(deltaTime, map);
	}
	else
	{
		handleSwimming(deltaTime, map);
	}
}

void Mario::HandleBridgeStanding(float deltaTime, std::vector<FlyingBridge*> bridges)
{
	sf::Vector2f newPosition = position;
	collisionBox.left = position.x;
	collisionBox.top = newPosition.y + velocity.y * deltaTime;

	bool hasCollided = false;

	for (FlyingBridge* bridge : bridges)
	{
		sf::FloatRect bridgeBox = bridge->getCollisionBox();

		if (collisionBox.intersects(bridgeBox))
		{
			if (velocity.y > 0 && position.y + collisionBox.height <= bridgeBox.top + 1)
			{
				position.y = bridgeBox.top - collisionBox.height;
				velocity.y = 0;
				isOnGround = true;
				hasCollided = true;
				position.x += bridge->getVelocity().x * deltaTime;
			}
			else if (velocity.y < 0 && position.y >= bridgeBox.top + bridgeBox.height)
			{
				position.y = bridgeBox.top + bridgeBox.height;
				velocity.y = 0;
			}

			position.y += bridge->getVelocity().y * deltaTime;
			hasCollided = true;
			break;
		}
	}
}

void Mario::updateSwimmingState(float deltaTime)
{
	outOfWaterTime -= 20.0f * deltaTime;
	if (outOfWaterTime <= 0) isSwimming = false;
}

void Mario::handleSwimming(float deltaTime, Map& map)
{
	// Applying gravity (Smaller gravity in water)
	velocity.y = 5.0f;
	sf::Vector2f newPosition = position;
	newPosition.y += velocity.y * deltaTime;
	collisionBox.left = position.x;
	collisionBox.top = newPosition.y;

	if (!mapCollision(map))
	{
		position.y = newPosition.y;
	}
	else {
		if (velocity.y > 0) {
			position.y = newPosition.y - velocity.y * deltaTime;
			velocity.y = 0;
		}
		else if (velocity.y < 0) {
			position.y = newPosition.y - velocity.y * deltaTime;
			velocity.y = 0;
		}
	}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sf::Vector2f newPosition = position;
		newPosition.y -= 10.0f * deltaTime; 
		collisionBox.left = position.x;
		collisionBox.top = newPosition.y;
		if (!mapCollision(map)) position.y = newPosition.y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sf::Vector2f newPosition = position;
		newPosition.y += 10.0f * deltaTime; 
		collisionBox.left = position.x;
		collisionBox.top = newPosition.y;
		if (!mapCollision(map)) position.y = newPosition.y;
	}

	// Calculate horizontal velocity
	velocity.x = (position.x - previousPos.x) / deltaTime;
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

void Mario::handleHorizontalMove(float deltaTime, Map& map)
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

void Mario::handleVerticalMove(float deltaTime, Map& map)
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
		if (invicibleTime2 <= 0)
		{
			SoundManager::getInstance().stopSound("invicible");
			SoundManager::getInstance().setVolume("main", 50);
		}
	}
}

void Mario::handleCollectCoin()
{
	if (coin >= 100)
	{
		SoundManager::getInstance().playSound("life-up");
		coin -= 100;
		life++;
	}
}

void Mario::handleJumpStrength()
{
	jumpStrength = (levelUp) ? 25.0f : 25.0f;
}

void Mario::UpdateTexture(float deltaTime)
{
	if (!levelUp)
	{
		if (!isSwimming)
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
			sprite.setTexture(*smallSwimAnimation.update(deltaTime));
		}
	}
	else
	{
		if (!isSwimming)
		{
			if (!isOnGround)
				bigSprite.setTexture(bigTexture[4]);
			else if (velocity.x != 0)
				bigSprite.setTexture(*bigRunAnimation.update(deltaTime));
			else if (isDead == true)
				bigSprite.setTexture(deadTexture);
			else bigSprite.setTexture(bigTexture[3]);
		}
		else
		{
			bigSprite.setTexture(*bigSwimAnimation.update(deltaTime));
		}
	}
}

void Mario::handleShoot(float deltaTime)
{
	shootCooldown -= deltaTime;
	if (shootingAbility == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && shootCooldown <= 0.0f)
	{
		SoundManager::getInstance().playSound("bullet");
		Bullet* newBullet = new Bullet;
		newBullet->Begin(position);
		newBullet->setVelocity(sf::Vector2f((facingRight ? 1 : -1) * 10.0f + velocity.x, 0.0f));
		bullets.push_back(newBullet);
		shootCooldown = shootCooldownTimer;
	}
}

void Mario::UpdateBullet(const float& deltaTime, const Map& map)
{
	if (bullets.size() > 0)
	{
		for (auto it = bullets.begin(); it != bullets.end(); it++)
		{
			(*it)->Update(deltaTime, map);
		}
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			if ((*it)->getAppearTime() <= 0.0f)
			{
				(*it)->Reset();
				delete (*it);
				it = bullets.erase(it);
			}
			else it++;
		}
	}
}

void Mario::DrawBullet(sf::RenderWindow& window)
{
	for (auto it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->Draw(window);
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

bool Mario::mapCollision(Map& map)
{
	const std::vector<std::vector<int>>& grid = map.getGrid();
	const auto& collisionBoxes = map.getCollisionBoxList();

	const std::set<int> solidBlocks = { 1, 2, 3, 4, 5, 11, 12, 13, 14, 24, 25, 26, 42, 44, 45, 46, 47};
	const int water = 43;
	const int waterSurface = 48;

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
			else if (collisionBox.intersects(currentBox) && (tileType == water || tileType == waterSurface))
			{
				isSwimming = true;
				outOfWaterTime = 2.0f;
			}
			else if (collisionBox.intersects(currentBox) && (tileType == 8 || tileType == 9))
			{
				isDead = true;
				return false;
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
	return (goombas.getCollisionBox().intersects(collisionBox) && goombas.getDieStatus() == false && isDead == false);
}

bool Mario::koopaCollision(Koopa& koopa)
{
	return (koopa.getCollisionBox().intersects(collisionBox) && koopa.getDieStatus() == false && isDead == false);
}

bool Mario::mushroomCollision(PowerUpMushroom& mushroom)
{
	return collisionBox.intersects(mushroom.getCollisionBox());
}

bool Mario::starCollision(InvicibleStar& star)
{
	return collisionBox.intersects(star.getCollisionBox());
}

bool Mario::flowerCollision(FireFlower& flower)
{
	return collisionBox.intersects(flower.getCollisionBox());
}

bool Mario::coinCollision(Coin& coin)
{
	return collisionBox.intersects(coin.getCollisionBox());
}

bool Mario::chomperCollision(Chomper& chomper)
{
	return (collisionBox.intersects(chomper.getCollisionBox()) && chomper.getHidingStatus() != true);
}

bool Mario::birdCollision(Bird& bird)
{
	return collisionBox.intersects(bird.getCollisionBox()) && bird.getDieStatus() == false;
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
	gravity = 60.0f;
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
	bigRunAnimation.Reset();
	smallSwimAnimation.Reset();
	bigSwimAnimation.Reset();
	smallWinAnimation.Reset();
	bigWinAnimation.Reset();
	textures.clear();
	bigTexture.clear();
	smallSwimTextures.clear();
	bigSwimTextures.clear();
	winTextures.clear();
	shootingAbility = false;
	isWinning = false;
	mapArchive = 1;
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
	gravity = 60.0f;
	isDead = false;
	deadTimer = 3.0f;
	v = 10.0f;
	tmpGravity = -30.0f;
	koopaKickSpeed = 20.0f;
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
	bigRunAnimation.Reset();
	smallSwimAnimation.Reset();
	bigSwimAnimation.Reset();
	smallWinAnimation.Reset();
	bigWinAnimation.Reset();
	textures.clear();
	bigTexture.clear();
	smallSwimTextures.clear();
	bigSwimTextures.clear();
	winTextures.clear();
	isWinning = false;
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

void Mario::setVelocity(const sf::Vector2f& value)
{
	velocity = value;
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

std::vector<Bullet*> Mario::getBullets() const
{
	return bullets;
}

bool Mario::getShootingStatus()
{
	return shootingAbility;
}

void Mario::setShootingStatus(const bool& value)
{
	shootingAbility = value;
}

bool Mario::getWinningState()
{
	return isWinning;
}

void Mario::setWinningState(const bool& value)
{
	isWinning = value;
}

float Mario::getJumpStrength() const
{
	return jumpStrength;
}

int Mario::getFacingRightStatus()
{
	return facingRight;
}

float Mario::getKoopaKickSpeed()
{
	return koopaKickSpeed;
}

int Mario::getCurrentCharacterSelected() const
{
	return characterSelected;
}
