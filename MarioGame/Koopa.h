#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Map.h"
class Koopa : public Enemy
{
private:
	sf::Texture shell;
	sf::Texture throwTexture;
	bool inShell;
	float v;
	float tmpGravity;
public:
	void Begin(const sf::Vector2f& koopaPosition);
	void Update(float deltaTime, const Map& map);

	bool getInShellStatus() const;
	void setInShellStatus(const bool& value);

	bool teamCollision(const Koopa& other);
};

