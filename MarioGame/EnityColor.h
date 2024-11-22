#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

enum class EntityType {
    Stone,
    Copper,
    Brick,
    useBlock,
    HiddenBox,
    Goomba,
    Koopa,
    Mario,
    None
};

sf::Color GoombaColor(200, 0, 0);
sf::Color KoopaColor(100, 0, 0);
sf::Color useBlockColor(100, 100, 0);

inline const std::unordered_map<EntityType, sf::Color> EntityColors = {
    {EntityType::Stone, sf::Color::Black},
    {EntityType::Copper, sf::Color::Blue},
    {EntityType::Brick, sf::Color::Green},
    {EntityType::useBlock, useBlockColor},
    {EntityType::HiddenBox, sf::Color::Yellow},
    {EntityType::Goomba, GoombaColor},
    {EntityType::Koopa, KoopaColor},
    {EntityType::Mario, sf::Color::Red},
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