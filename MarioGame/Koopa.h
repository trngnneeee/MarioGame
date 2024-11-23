#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Map.h"

class Koopa : public Enemy
{
private:
	sf::Texture shell;
	bool inShell;
	
	sf::Texture outShell[4];
	Animation outAnimation;
	
	sf::Texture throwTexture;

	float standTimer;

	// accelaration
	float friction = 0.98f;
public:
	Koopa();

	void Begin(const sf::Vector2f& koopaPosition);
	void Update(float deltaTime, const Map& map);

	bool teamCollision(const Koopa& other);

	// Setter/Getter
	bool getInShellStatus() const;
	void setInShellStatus(const bool& value);


	void setStandTimer(const float& value);
};

