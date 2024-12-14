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
    None,
    Stick,
    Circle, // Win point
    EndWinPoint,
    Fire1, Fire2, Fire3,
    Coin,
    Tube1, Tube2, Tube3, Tube4,
    CastleBrick, CastleDoorTop, CastleDoorBottom, CastleTop, CastleTopFill, CastleWindowLeft, CastleWindowRight,
    Collumn, Floor, FloorLeft, FloorRight,
    bigBushLeft, bigBushMid, bigBushRight,
    cloudBottomLeft, cloudBottomMid, cloudBottomRight, cloudTopLeft, cloudTopMid, cloudTopRight,
    triBushAdditional, triBushLeft, triBushMid, triBushRight, triBushTop,
    Chomper,
    Coral, greenBlock, Water,
    blueTube1, blueTube2, blueTube3, blueTube4
};

sf::Color GoombaColor(200, 0, 0);
sf::Color KoopaColor(100, 0, 0);
sf::Color useBlockColor(100, 100, 0);

sf::Color stickColor(0, 150, 0);
sf::Color circleColor(0, 100, 0);
sf::Color endWinPointColor(123, 123, 123);

sf::Color fireColor1(0, 0, 100);
sf::Color fireColor2(0, 0, 120);
sf::Color fireColor3(0, 0, 140);

sf::Color coinColor(200, 200, 0);

sf::Color tubeColor1(0, 120, 0);
sf::Color tubeColor2(0, 140, 0);
sf::Color tubeColor3(0, 160, 0);
sf::Color tubeColor4(0, 180, 0);

sf::Color castleBrick(100, 40, 15);
sf::Color castleDoorTop(100, 60, 15);
sf::Color castleDoorBottom(100, 80, 15);
sf::Color castleTop(100, 100, 15);
sf::Color castleTopFill(100, 120, 15);
sf::Color castleWindowLeft(100, 140, 15);
sf::Color castleWindowRight(100, 160, 15);

sf::Color collum(0, 0, 50);
sf::Color floorColor(0, 50, 50);
sf::Color floorLeft(0, 30, 50);
sf::Color floorRight(0, 80, 50);

sf::Color bigBushLeftColor(124, 252, 0);
sf::Color bigBushMidColor(127, 255, 0);
sf::Color bigBushRightColor(173, 255, 47);

sf::Color cloudBottomLeftColor(251, 252, 248);
sf::Color cloudBottomMidColor(254, 249, 243);
sf::Color cloudBottomRightColor(245, 254, 253);
sf::Color cloudTopLeftColor(253, 246, 228);
sf::Color cloudTopMidColor(255, 250, 218);
sf::Color cloudTopRightColor(255, 249, 227);

sf::Color triBushAdditionalColor(0, 250, 154);
sf::Color triBushLeftColor(0, 255, 127);
sf::Color triBushMidColor(46, 139, 87);
sf::Color triBushRightColor(102, 205, 170);
sf::Color triBushTopColor(60, 179, 113);

sf::Color chomperColor(0, 234, 0);

sf::Color coralColor(255, 0, 145); //ff0091
sf::Color greenBlockColor(53, 94, 59); //355e3b
sf::Color waterColor(68, 108, 207); //46ccf

sf::Color blueTube1Color(204, 119, 34);
sf::Color blueTube2Color(205, 170, 110);
sf::Color blueTube3Color(251, 236, 93);
sf::Color blueTube4Color(253, 253, 150);

inline const std::unordered_map<EntityType, sf::Color> EntityColors = {
    {EntityType::Stone, sf::Color::Black},
    {EntityType::Copper, sf::Color::Blue},
    {EntityType::Brick, sf::Color::Green},
    {EntityType::useBlock, useBlockColor},

    {EntityType::HiddenBox, sf::Color::Yellow},

    {EntityType::Goomba, GoombaColor},
    {EntityType::Koopa, KoopaColor},
    {EntityType::Mario, sf::Color::Red},
    
    {EntityType::Stick, stickColor},
    {EntityType::Circle, circleColor},
    {EntityType::EndWinPoint, endWinPointColor},

    {EntityType::Fire1, fireColor1},
    {EntityType::Fire2, fireColor2},
    {EntityType::Fire3, fireColor3},

    {EntityType::Coin, coinColor},

    {EntityType::Tube1, tubeColor1},
    {EntityType::Tube2, tubeColor2},
    {EntityType::Tube3, tubeColor3},
    {EntityType::Tube4, tubeColor4},

    {EntityType::CastleBrick, castleBrick},
    {EntityType::CastleDoorTop, castleDoorTop},
    {EntityType::CastleDoorBottom, castleDoorBottom},
    {EntityType::CastleTop, castleTop},
    {EntityType::CastleTopFill, castleTopFill},
    {EntityType::CastleWindowLeft, castleWindowLeft},
    {EntityType::CastleWindowRight, castleWindowRight},

    {EntityType::Collumn, collum},
    {EntityType::Floor, floorColor},
    {EntityType::FloorLeft, floorLeft},
    {EntityType::FloorRight, floorRight},

    {EntityType::bigBushLeft, bigBushLeftColor},
    {EntityType::bigBushMid, bigBushMidColor},
    {EntityType::bigBushRight, bigBushRightColor},
    {EntityType::cloudBottomLeft, cloudBottomLeftColor},
    {EntityType::cloudBottomMid, cloudBottomMidColor},
    {EntityType::cloudBottomRight, cloudBottomRightColor},
    {EntityType::cloudTopLeft, cloudTopLeftColor},
    {EntityType::cloudTopMid, cloudTopMidColor},
    {EntityType::cloudTopRight, cloudTopRightColor},
    {EntityType::triBushAdditional, triBushAdditionalColor},
    {EntityType::triBushLeft, triBushLeftColor},
    {EntityType::triBushMid, triBushMidColor},
    {EntityType::triBushRight, triBushRightColor},
    {EntityType::triBushTop, triBushTopColor},

    {EntityType::Chomper, chomperColor},

    {EntityType::Coral, coralColor},
    {EntityType::greenBlock, greenBlockColor},
    {EntityType::Water, waterColor},

    {EntityType::blueTube1, blueTube1Color},
    {EntityType::blueTube2, blueTube2Color},
    {EntityType::blueTube3, blueTube3Color},
    {EntityType::blueTube4, blueTube4Color},


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