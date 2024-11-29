#include "Koopa.h"

Koopa::Koopa()
	: outAnimation(0.4f), inShell(false), standTimer(3.0f)
{
}

Koopa* Koopa::clone() const
{
	return new Koopa(*this);
}

void Koopa::Begin(const sf::Vector2f& koopaPosition)
{
	// Koopa default
	for (int i = 0; i < 2; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Koopa/koopa" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 2; i++)
	{
		runAnimation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	if (!shell.loadFromFile("./resources/textures/Koopa/koopashell.png"))
		return;
	if (!throwTexture.loadFromFile("./resources/textures/Koopa/koopaDead.png"))
		return;
	// Out of shell
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Koopa/koopaOut" + std::to_string(i + 1) + ".png");
		outShell.push_back(tmp);
	}
	for (int i = 0; i < outShell.size(); i++)
	{
		outAnimation.addFrame(Frame(&outShell[i], 0.1f * (i + 1)));
	}

	// Init start position
	position = koopaPosition;

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		0.9f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);
}

void Koopa::Update(float deltaTime, const Map& map)
{
	if (handleDead(deltaTime)) return;
	updateTexture(deltaTime);
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);
	updateScale();
}

bool Koopa::handleDead(float deltaTime)
{
	if (isDead)
	{
		position.y -= v * deltaTime;
		v += tmpGravity * deltaTime;
		sprite.setTexture(throwTexture);
		if (dieTime > 0)
		{
			dieTime -= deltaTime;
			if (!score)
				score = new FloatingScore(200, position);
			else
				score->Update(deltaTime);
		}
		else
			if (score) delete score;
		return true;
	}
	return false;
}

bool Koopa::handleOutOfShell(float deltaTime)
{
	if (velocity.x == 0)
	{
		standTimer -= deltaTime;
		if (standTimer <= 1.5f) sprite.setTexture(*outAnimation.update(deltaTime));
		if (standTimer <= 0)
		{
			inShell = false;
			velocity.x = 3.0f;
			standTimer = 3.0f;
			return true;
		}
	}
	else 
	{
		standTimer = 10.0f;
		return false;
	}
}

void Koopa::updateTexture(float deltaTime)
{
	if (inShell)
	{
		velocity.x *= friction;
		if (std::abs(velocity.x) < 0.5f)
		{
			velocity.x = 0.0f;
		}
		sprite.setTexture(shell);
		if (handleOutOfShell(deltaTime)) return;
	}
	else
		sprite.setTexture(*runAnimation.update(deltaTime));
}

void Koopa::updateScale()
{
	if (velocity.x < 0)
	{
		sprite.setOrigin(0, 0);
		sprite.setScale(sf::Vector2f(0.9f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
	}
	else
	{
		sprite.setOrigin(textures[0].getSize().x, 0);
		sprite.setScale(sf::Vector2f(0.9f / textures[0].getSize().x * -1, 1.0f / textures[0].getSize().y));
	}
}

bool Koopa::teamCollision(const Koopa& other)
{
	return (inShell == true && other.getInShellStatus() == false && std::abs(velocity.x) > 5.0f && collisionBox.intersects(other.collisionBox));
}

void Koopa::Reset()
{
	runAnimation.Reset();
	textures.clear();
	if (score) delete score;
	outShell.clear();
	outAnimation.Reset();
}

bool Koopa::getInShellStatus() const
{
	return inShell;
}

void Koopa::setInShellStatus(const bool& value)
{
	inShell = value;
}

void Koopa::setStandTimer(const float& value)
{
	standTimer = value;
}
