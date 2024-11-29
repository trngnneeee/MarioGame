#include "EnemyFactory.h"

EnemyFactory::EnemyFactory()
{
    prototypes["Goomba"] = new Goombas();
    prototypes["Koopa"] = new Koopa();
}

EnemyFactory::~EnemyFactory()
{
    for (auto& pair : prototypes) {
        delete pair.second;
    }
}

Enemy* EnemyFactory::createEnemy(const std::string& enemyType) const
{
    if (prototypes.find(enemyType) != prototypes.end()) {
        return prototypes.at(enemyType)->clone();
    }
    return nullptr;
}
