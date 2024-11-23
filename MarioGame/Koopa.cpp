#include "Koopa.h"

Koopa::Koopa()
	: outAnimation(0.4f), inShell(false), standTimer(3.0f)
{
}

void Koopa::Begin(const sf::Vector2f& koopaPosition)
{
	sf::Texture texture1, texture2;
	if (!texture1.loadFromFile("./resources/textures/koopa1.png"))
		return;
	if (!texture2.loadFromFile("./resources/textures/koopa2.png"))
		return;
	if (!shell.loadFromFile("./resources/textures/koopashell.png"))
		return;
	if (!throwTexture.loadFromFile("./resources/textures/koopaDead.png"))
		return;
	if (!outShell[0].loadFromFile("./resources/textures/koopaOut1.png"))
		return;
	if (!outShell[1].loadFromFile("./resources/textures/koopaOut2.png"))
		return;
	if (!outShell[2].loadFromFile("./resources/textures/koopaOut3.png"))
		return;
	if (!outShell[3].loadFromFile("./resources/textures/koopaOut4.png"))
		return;
	textures.push_back(texture1);
	textures.push_back(texture2);
	

	// Init sprite
	sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));

	// Init start position
	position = koopaPosition;

	// Init run animation
	runAnimation.addFrame(Frame(&textures[0], 0.1f));
	runAnimation.addFrame(Frame(&textures[1], 0.2f));

	// Init collision box
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f / textures[0].getSize().x,
		1.0f / textures[0].getSize().y
	);

	// Init get out shell animation
	outAnimation.addFrame(Frame(&outShell[0], 0.1f));
	outAnimation.addFrame(Frame(&outShell[1], 0.2f));
	outAnimation.addFrame(Frame(&outShell[2], 0.3f));
	outAnimation.addFrame(Frame(&outShell[3], 0.4f));
}

void Koopa::Update(float deltaTime, const Map& map)
{
	if (isDead)
	{
		position.y -= v * deltaTime;
		v += tmpGravity * deltaTime;
		sprite.setTexture(throwTexture);
		dieTime -= deltaTime;
		if (!score)
			score = new FloatingScore(200, position);
		else
			score->Update(deltaTime);
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
		sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
	}
	else
	{
		sprite.setOrigin(textures[0].getSize().x, 0);
		sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x * -1, 1.0f / textures[0].getSize().y));
	}
}

bool Koopa::teamCollision(const Koopa& other)
{
	return (inShell == true && other.getInShellStatus() == false && std::abs(velocity.x) > 5.0f && collisionBox.intersects(other.collisionBox));
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
