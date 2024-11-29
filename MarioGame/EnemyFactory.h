#pragma once
#include "Enemy.h"
#include "Goombas.h"
#include "Koopa.h"
#include <unordered_map>
#include <string>

class EnemyFactory
{
private:
	std::unordered_map<std::string, Enemy*> prototypes;
public:
    // Constructors
    EnemyFactory();
    // Destructors
    ~EnemyFactory();

    // Functions
    Enemy* createEnemy(const std::string& enemyType) const;
};

