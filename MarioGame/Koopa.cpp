#include "Koopa.h"

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

	// Init default value
	inShell = false;

	// Init value for dead animation
	v = 10.0f;
	tmpGravity = -30.0f;
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
			score = new FloatingScore(100, position);
		else
			score->Update(deltaTime);
		return;
	}
	// Update texture
	if (inShell)
		sprite.setTexture(shell);
	else
		sprite.setTexture(*runAnimation.update(deltaTime));
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

bool Koopa::getInShellStatus() const
{
	return inShell;
}

void Koopa::setInShellStatus(const bool& value)
{
	inShell = value;
}

bool Koopa::teamCollision(const Koopa& other)
{
	return (velocity.x != 0 && inShell == true && other.inShell == false && collisionBox.intersects(other.collisionBox));
}
