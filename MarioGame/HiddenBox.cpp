#include "HiddenBox.h"

HiddenBox::HiddenBox()
	: animation(0.3f), used(false)
{
}

void HiddenBox::Begin(const sf::Vector2f& position)
{
	for (int i = 0; i < 3; i++)
	{
		sf::Texture tmp;
		tmp.loadFromFile("./resources/textures/HiddenBox/hiddenbox" + std::to_string(i + 1) + ".png");
		textures.push_back(tmp);
	}
	for (int i = 0; i < 3; i++)
	{
		animation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
	}
	usedTexture.loadFromFile("./resources/textures/block.png");
	this->position = position;
	collisionBox = sf::FloatRect(
		position.x,
		position.y,
		1.0f,
		1.0f
	);
}

void HiddenBox::Update(const float& deltaTime)
{
	collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	if (used) sprite.setTexture(usedTexture);
	else sprite.setTexture(*animation.update(deltaTime));
}

void HiddenBox::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));
	window.draw(sprite);
}

void HiddenBox::Reset()
{
	animation.Reset();
	textures.clear();
}

sf::FloatRect HiddenBox::getCollisionBox() const
{
	return collisionBox;
}

sf::Vector2f HiddenBox::getPosition() const
{
	return position;
}

bool HiddenBox::getUsedStatus() const
{
	return used;
}

void HiddenBox::setUsedStatus(const bool& value)
{
	used = value;
}
