#pragma once
#include "Enemy.h"
#include "Koopa.h"

class Goombas : public Enemy
{
private:
	bool isDeadByKoopa;
	sf::Texture throwTexture;
public:
	// Constructor
	Goombas();

	// Functions
	void Begin(const sf::Vector2f& position) override;
	void Update(float deltaTime, const Map& map) override;
	
	bool handleDead(float deltaTime);
	bool handleDeadByKoopa(float deltaTime);
	void handleTeamCollision();

	// Collision
	bool teamCollision(const Goombas& other);
	bool koopaCollision(const Koopa& koopa);

	// Setter/Getter
	bool getDieByKoopaStatus();
	void setDieByKoopaStatus(const bool& value);
};

