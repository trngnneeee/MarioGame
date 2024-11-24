#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "FloatingScore.h"
#include "Animation.h"
#include <string>

class Map;

class Coin
{
private:
    sf::Sprite sprite;  
    std::vector<sf::Texture> textures;
    Animation coinAnimation;

    sf::Vector2f position;
    
    sf::SoundBuffer coinSoundBuffer;
    sf::Sound coinSound;
    bool isPlayed;
    
    bool collected;  
    float disappearTime;
    FloatingScore* score;

    sf::FloatRect collisionBox;
public:
    Coin();
    // Functions
    void Begin(sf::Vector2f position);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    // Setter/Getter
    bool isCollected() const;
    void setCollected(const bool& value);

    sf::FloatRect getCollisionBox() const;

    float getDisapperTime();
};

