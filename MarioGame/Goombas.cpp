#include "Goombas.h"
#include <iostream>

Goombas::Goombas()
	: isDeadByKoopa(false)
{
}

Goombas* Goombas::clone() const
{
	return new Goombas(*this);
}

void Goombas::Begin(const sf::Vector2f& goombasPosition)
{
	// Init texture
	sf::Texture texture1, texture2;
	if (!texture1.loadFromFile("./resources/textures/Goomba/goombas1.png"))
		return;
	if (!texture2.loadFromFile("./resources/textures/Goomba/goombas2.png"))
		return;
	if (!deadTexture.loadFromFile("./resources/textures/Goomba/goombasDead.png"))
		return;
	if (!throwTexture.loadFromFile("./resources/textures/Goomba/goombasDead2.png"))
		return;
	textures.push_back(texture1);
	textures.push_back(texture2);

	// Init sprite
	sprite.setScale(sf::Vector2f(0.9f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));

	// Init start position
	position = goombasPosition;
	
	// Init run animation
	runAnimation.addFrame(Frame(&textures[0], 0.1f));
	runAnimation.addFrame(Frame(&textures[1], 0.2f));

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		0.9f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);
}

void Goombas::Update(float deltaTime, const Map& map)
{
	if (handleDead(deltaTime)) return;
	if (handleDeadByKoopa(deltaTime)) return;
	// Update texture
	sprite.setTexture(*runAnimation.update(deltaTime));
	// Update collision
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	// Handle Move
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);
}

bool Goombas::handleDead(float deltaTime)
{
	if (isDead)
	{
		sprite.setTexture(deadTexture);
		velocity.x = 0;
		velocity.y = 0;
		if (dieTime > 0)
		{
			dieTime -= deltaTime;
		}
		return true;
	}
	return false;
}

bool Goombas::handleDeadByKoopa(float deltaTime)
{
	if (isDeadByKoopa)
	{
		position.y -= v * deltaTime;
		v += tmpGravity * deltaTime;
		sprite.setTexture(throwTexture);
		dieTime -= deltaTime;
		return true;
	}
	return false;
}

bool Goombas::teamCollision(const Goombas& other)
{
	return (collisionBox.intersects(other.collisionBox));
}

void Goombas::handleTeamCollision()
{
	velocity.x = -velocity.x;
}

bool Goombas::koopaCollision(const Koopa& koopa)
{
	return (koopa.getVelocity().x != 0 && std::abs(koopa.getVelocity().x) > 5.0f && koopa.getInShellStatus() == true && collisionBox.intersects(koopa.getCollisionBox()));
}

bool Goombas::getDieByKoopaStatus()
{
	return isDeadByKoopa;
}

void Goombas::setDieByKoopaStatus(const bool& value)
{
	isDeadByKoopa = value;
}

void Goombas::setSpeedBasedOnMapType(const int& mapType)
{
	switch (mapType) {
	case 1:
		setSpeedStrategy(new NormalSpeedStrategy());
		break;
	case 2:
		setSpeedStrategy(new FastSpeedStrategy());
		break;
	case 3:
		setSpeedStrategy(new SuperFastSpeedStrategy());
		break;
	default:
		setSpeedStrategy(new NormalSpeedStrategy());
		break;
	}
	velocity.x = getSpeedStrategy();
}
