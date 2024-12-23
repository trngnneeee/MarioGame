#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class Bird : public Enemy
{
private:
	float maxRangeX, minRangeX, maxRangeY, minRangeY;
	sf::Texture deadTexture;
public:
	// Constructors
	Bird* clone() const override;

	// Functions
	void Begin(const sf::Vector2f& position) override;
	void Update(float deltaTime, const Map& map) override;
	void UpdateScale();
	bool HandleDead(const float& deltaTime);

	// Setter/Getter
	sf::FloatRect getCollisionBox() const;
};

