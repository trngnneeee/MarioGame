#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Enemy.h"
#include "Map.h"
#include "NormalSpeedStrategy.h"
#include "FastSpeedStrategy.h"
#include "SuperFastSpeedStrategy.h"
class Koopa : public Enemy
{
private:
	sf::Texture shell;
	bool inShell;
	
	std::vector<sf::Texture> outShell;
	Animation outAnimation;
	
	sf::Texture throwTexture;

	float standTimer;

	// accelaration
	float friction = 0.98f;
public:
	// Constructors
	Koopa();
	Koopa* clone() const override;


	// Functions
	void Begin(const sf::Vector2f& koopaPosition) override;
	void Update(float deltaTime, const Map& map) override;
	void Reset();

	bool handleDead(float deltaTime);
	bool handleOutOfShell(float deltaTime);
	void updateTexture(float deltaTime);
	void updateScale();

	// Collision
	bool teamCollision(const Koopa& other);

	// Setter/Getter
	bool getInShellStatus() const;
	void setInShellStatus(const bool& value);
	void setStandTimer(const float& value);

	void setSpeedBasedOnMapType(int mapType);
};

