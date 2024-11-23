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

	void Begin(const sf::Vector2f& goombasPosition);
	void Update(float deltaTime, const Map& map);

	bool teamCollision(const Goombas& other);
	void handleTeamCollision();

	bool koopaCollision(const Koopa& koopa);

	// Setter/Getter
	bool getDieByKoopaStatus();
	void setDieByKoopaStatus(const bool& value);
};

