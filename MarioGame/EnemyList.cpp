#include "EnemyList.h"

void EnemyList::Begin(std::vector<sf::Vector2f> enemiesPosition)
{
	for (int i = 0; i < enemiesPosition.size(); i++)
	{
		Enemy* newEnemy = new Enemy;
		newEnemy->setPosition(enemiesPosition[i]);
		newEnemy->Begin();
		enemies.push_back(newEnemy);
	}
}

void EnemyList::Update(const float& deltaTime, const Map& map)
{

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(deltaTime, map);
	}

	handleTeamCollision();

	// Erase enemies that have died
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		if (((*it)->getDieStatus() == true) && ((*it)->getDieTime() <= 0))
			it = enemies.erase(it);  
		else
			++it; 
	}	
}

void EnemyList::handleTeamCollision()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = i + 1; j < enemies.size(); j++)
		{
			if (enemies[i]->teamCollision(*enemies[j]) && enemies[i]->getDieStatus() == false && enemies[j]->getDieStatus() == false)
			{
				enemies[i]->setVelocity();
				enemies[j]->setVelocity();
			}
		}
	}
}

void EnemyList::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw(window);
	}
}

void EnemyList::Reset()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();
}

int EnemyList::getSize()
{
	return enemies.size();
}

Enemy& EnemyList::getEnemy(int index)
{
	return *enemies[index];
}
