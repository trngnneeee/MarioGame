#include "Koopa.h"

Koopa::Koopa()
	: outAnimation(0.4f), inShell(false), standTimer(3.0f)
{
}

void Koopa::Begin(const sf::Vector2f& koopaPosition)
{
	sf::Texture texture1, texture2;
	if (!texture1.loadFromFile("./resources/textures/Koopa/koopa1.png"))
		return;
	if (!texture2.loadFromFile("./resources/textures/Koopa/koopa2.png"))
		return;
	textures.push_back(texture1);
	textures.push_back(texture2);
	if (!shell.loadFromFile("./resources/textures/Koopa/koopashell.png"))
		return;
	if (!throwTexture.loadFromFile("./resources/textures/Koopa/koopaDead.png"))
		return;
	for (int i = 0; i < 4; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/Koopa/koopaOut" + std::to_string(i + 1) + ".png");
		outShell.push_back(tmp);
	}
	// Init get out shell animation
	for (int i = 0; i < outShell.size(); i++)
	{
		outAnimation.addFrame(Frame(&outShell[i], 0.1f * (i + 1)));
	}

	// Init sprite
	sprite.setScale(sf::Vector2f(0.9f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));

	// Init start position
	position = koopaPosition;

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

void Koopa::Update(float deltaTime, const Map& map)
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
		return;
	}
	// Update texture
	if (inShell)
	{
		velocity.x *= friction;
		if (std::abs(velocity.x) < 0.5f)
		{
			velocity.x = 0.0f;
		}
		sprite.setTexture(shell);
		if (velocity.x == 0)
		{
			standTimer -= deltaTime;
			if (standTimer <= 1.5f) sprite.setTexture(*outAnimation.update(deltaTime));
			if (standTimer <= 0)
			{
				inShell = false;
				velocity.x = 3.0f;
				standTimer = 3.0f;
				return;
			}
		}
		else standTimer = 10.0f;
	}
	else
	{
		sprite.setTexture(*runAnimation.update(deltaTime));
	}
	// Update collision
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	// Handle Move
	handleHorizontalMove(deltaTime, map);
	handleVerticalMove(deltaTime, map);
	// Update scale
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
