﻿#include "Coin.h"

Coin::Coin()
    : collected(false), coinAnimation(1.0f), disappearTime(3.0f), isPlayed(false)
{
}

void Coin::Begin(sf::Vector2f position)
{
    // Init textures
    for (int i = 0; i < 10; i++)
    {
        sf::Texture tmp;
        tmp.loadFromFile("./resources/textures/coin" + std::to_string(i + 1) + ".png");
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

    // Init sound buffer
    if (!coinSoundBuffer.loadFromFile("resources/soundEffect/coin.mp3")) {
        // Kiểm tra lỗi nếu không tải được âm thanh
        std::cerr << "Không thể tải âm thanh coin!" << std::endl;
    }
    coinSound.setBuffer(coinSoundBuffer);

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
        if (!isPlayed)
        {
            isPlayed = true;
            coinSound.play();
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
            if (score) delete score;
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
