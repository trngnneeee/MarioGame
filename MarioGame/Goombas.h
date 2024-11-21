#pragma once
#include "Enemy.h"

class Goombas : public Enemy
{
private:
	
public:
	// Constructor
	Goombas();

	void Begin(const sf::Vector2f& goombasPosition);
	void Update(float deltaTime, const Map& map);

	bool teamCollision(const Goombas& other);
	void handleTeamCollision();
};

