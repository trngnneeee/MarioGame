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

Enemy* EnemyFactory::createItem(const std::string& itemType) const
{
    if (prototypes.find(itemType) != prototypes.end()) {
        return prototypes.at(itemType)->clone();
    }
    return nullptr;
}
