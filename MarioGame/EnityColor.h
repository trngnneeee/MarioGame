#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

enum class EntityType {
    Stone,
    Copper,
    Brick,
    useBlock,
    HiddenBox, HiddenBox2,
    Goomba,
    Koopa,
    Mario,
    None,
    Win,
    Stick,
    Circle,
    Fire1, Fire2, Fire3,
    Coin,
    Tube1, Tube2, Tube3, Tube4
};

sf::Color GoombaColor(200, 0, 0);
sf::Color KoopaColor(100, 0, 0);
sf::Color useBlockColor(100, 100, 0);
sf::Color winColor(0, 255, 255);
sf::Color stickColor(0, 150, 0);
sf::Color circleColor(0, 100, 0);

sf::Color fireColor1(0, 0, 100);
sf::Color fireColor2(0, 0, 120);
sf::Color fireColor3(0, 0, 140);

sf::Color coinColor(200, 200, 0);

sf::Color tubeColor1(0, 120, 0);
sf::Color tubeColor2(0, 140, 0);
sf::Color tubeColor3(0, 160, 0);
sf::Color tubeColor4(0, 180, 0);

sf::Color hiddenBox2Color(150, 100, 0);

inline const std::unordered_map<EntityType, sf::Color> EntityColors = {
    {EntityType::Stone, sf::Color::Black},
    {EntityType::Copper, sf::Color::Blue},
    {EntityType::Brick, sf::Color::Green},
    {EntityType::useBlock, useBlockColor},

    {EntityType::HiddenBox, sf::Color::Yellow},
    {EntityType::HiddenBox2, hiddenBox2Color},

    {EntityType::Goomba, GoombaColor},
    {EntityType::Koopa, KoopaColor},
    {EntityType::Mario, sf::Color::Red},
    
    {EntityType::Win, winColor},

    {EntityType::Stick, stickColor},
    {EntityType::Circle, circleColor},

    {EntityType::Fire1, fireColor1},
    {EntityType::Fire2, fireColor2},
    {EntityType::Fire3, fireColor3},

    {EntityType::Coin, coinColor},

    {EntityType::Tube1, tubeColor1},
    {EntityType::Tube2, tubeColor2},
    {EntityType::Tube3, tubeColor3},
    {EntityType::Tube4, tubeColor4},

    {EntityType::None, sf::Color::Transparent}
};

inline EntityType getEntityTypeFromColor(const sf::Color& color) {
    for (const auto& pair : EntityColors) {
        if (pair.second == color) {
            return pair.first;
        }
    }
    return EntityType::None; // Default to None if no match
}