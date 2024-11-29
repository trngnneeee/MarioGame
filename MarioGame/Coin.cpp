#include "Coin.h"

Coin::Coin()
    : collected(false), coinAnimation(1.0f), disappearTime(0.3f)
{
}

void Coin::Begin(const sf::Vector2f& position)
{
    // Init textures
    for (int i = 0; i < 10; i++)
    {
        sf::Texture tmp;
        tmp.loadFromFile("./resources/textures/Coin/coin" + std::to_string(i + 1) + ".png");
        textures.push_back(tmp);
    }

    // Init animation
    for (int i = 0; i < textures.size(); i++)
    {
        coinAnimation.addFrame(Frame(&textures[i], 0.1f * (i + 1)));
    }

    sprite.setScale(sf::Vector2f(1.0f / textures[0].getSize().x, 1.0f / textures[0].getSize().y));

    // Init position
    this->position = position;

    // Init collision box
    collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Coin::Update(float deltaTime)
{
    // Update collision box
    collisionBox = sf::FloatRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    sprite.setTexture(*coinAnimation.update(deltaTime));
    if (collected)
    {
        if (!SoundManager::getInstance().getPlayedStatus("coin"))
        {
            SoundManager::getInstance().playSound("coin");
            SoundManager::getInstance().setPlayedStatus("coin", true);
        }
        sprite.setColor(sf::Color(255, 255, 255, 0));
        disappearTime -= deltaTime;
        if (disappearTime > 0)
        {
            if (!score)
                score = new FloatingScore(100, position);
            else
                score->Update(deltaTime);
        }
        else
        {
            if (score) delete score;
            SoundManager::getInstance().setPlayedStatus("coin", false);
        }
    }
}

void Coin::Draw(sf::RenderWindow& window)
{
    sprite.setPosition(position);
    window.draw(sprite);
    if (score)
        score->Draw(window);
}

void Coin::Reset()
{
    coinAnimation.Reset();
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::setCollected(const bool& value)
{
    collected = value;
}

sf::FloatRect Coin::getCollisionBox() const
{
    return collisionBox;
}

float Coin::getDisapperTime()
{
    return disappearTime;
}
