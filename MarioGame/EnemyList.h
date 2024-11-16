#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
class EnemyList
{
private:
	std::vector<Enemy*> enemies;
public:
	void Begin(std::vector<sf::Vector2f> enemiesPosition);
	void Update(const float& deltaTime, const Map& map);
	void handleTeamCollision();
	void Draw(sf::RenderWindow& window);
	void Reset();

	int getSize();
	Enemy& getEnemy(int index);
};

