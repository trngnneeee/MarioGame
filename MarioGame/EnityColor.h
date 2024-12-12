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
    Tube1, Tube2, Tube3, Tube4,
    blueTube1, blueTube2, blueTube3, blueTube4,
    CastleBrick, CastleDoorTop, CastleDoorBottom, CastleTop, CastleTopFill, CastleWindowLeft, CastleWindowRight,
    Collumn, Floor, FloorLeft, FloorRight,
    bigBushLeft, bigBushMid, bigBushRight,
    cloudBottomLeft, cloudBottomMid, cloudBottomRight, cloudTopLeft, cloudTopMid, cloudTopRight,
    triBushAdditional, triBushLeft, triBushMid, triBushRight, triBushTop,
    Coral, greenBlock, Water,
    Chomper
};

sf::Color GoombaColor(200, 0, 0); //c80000
sf::Color KoopaColor(100, 0, 0); //640000
sf::Color useBlockColor(100, 100, 0); //646400
sf::Color winColor(0, 255, 255); //00ffff

sf::Color stickColor(0, 150, 0); //009600
sf::Color circleColor(0, 100, 0); //006400

sf::Color fireColor1(0, 0, 100); //000064 top
sf::Color fireColor2(0, 0, 120); //000078 mid
sf::Color fireColor3(0, 0, 140); //00008c bottom

sf::Color coinColor(200, 200, 0); //c8c800

sf::Color tubeColor1(0, 120, 0); //007800 tube top left
sf::Color tubeColor2(0, 140, 0); //008c00 tube top right
sf::Color tubeColor3(0, 160, 0); //00a000 tube bottom left
sf::Color tubeColor4(0, 180, 0); //00b400 tube bottom right

sf::Color blueTubeColor1(204, 119, 34); //cc7722 
sf::Color blueTubeColor2(205, 170, 110); //cdaa6e
sf::Color blueTubeColor3(251,236,93); //fbec5d
sf::Color blueTubeColor4(252,252,150); //fdfd96

sf::Color castleBrick(100, 40, 15); //64280f
sf::Color castleDoorTop(100, 60, 15); //643c0f
sf::Color castleDoorBottom(100, 80, 15); //64500f
sf::Color castleTop(100, 100, 15); //64640f
sf::Color castleTopFill(100, 120, 15); //64780f
sf::Color castleWindowLeft(100, 140, 15); //648c0f
sf::Color castleWindowRight(100, 160, 15); //64a00f

sf::Color collum(0, 0, 50); //000032
sf::Color floorColor(0, 50, 50); //003232
sf::Color floorLeft(0, 30, 50); //001e32
sf::Color floorRight(0, 80, 50); //005032

sf::Color bigBushLeftColor(124, 252, 0); //7cfc00
sf::Color bigBushMidColor(127, 255, 0); //7fff00
sf::Color bigBushRightColor(173, 255, 47); //adff2f

sf::Color cloudBottomLeftColor(251, 252, 248); //fbfcf8
sf::Color cloudBottomMidColor(254, 249, 243); //fef9f3
sf::Color cloudBottomRightColor(245, 254, 253); //f5fefd
sf::Color cloudTopLeftColor(253, 246, 228); //fdf6e4
sf::Color cloudTopMidColor(255, 250, 218); //fffada
sf::Color cloudTopRightColor(255, 249, 227); //fff9e3

sf::Color triBushAdditionalColor(0, 250, 154); //00fa9a
sf::Color triBushLeftColor(0, 255, 127); //00ff7f
sf::Color triBushMidColor(46, 139, 87); //2e8b57
sf::Color triBushRightColor(102, 205, 170); //66cdaa
sf::Color triBushTopColor(60, 179, 113); //3cb371

sf::Color coralColor(255, 0, 145); //ff0091
sf::Color greenBlockColor(53, 94, 59); //355e3b
sf::Color waterColor(68, 108, 207); //46ccf

sf::Color chomperColor(0, 234, 0);

inline const std::unordered_map<EntityType, sf::Color> EntityColors = {
    {EntityType::Stone, sf::Color::Black},
    {EntityType::Copper, sf::Color::Blue},
    {EntityType::Brick, sf::Color::Green},
    {EntityType::useBlock, useBlockColor},

    {EntityType::HiddenBox, sf::Color::Yellow},

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

    {EntityType::blueTube1, blueTubeColor1},
    {EntityType::blueTube2, blueTubeColor2},
    {EntityType::blueTube3, blueTubeColor3},
    {EntityType::blueTube4, blueTubeColor4},

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

    {EntityType::Coral, coralColor},
    {EntityType::greenBlock, greenBlockColor},
    {EntityType::Water, waterColor},

    {EntityType::Chomper, chomperColor},

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
