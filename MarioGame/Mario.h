#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Renderer.h"
#include "Map.h"

class Mario
{
private:
	double verticalVelocity{};
	double gravity{ 9.8f };
	bool isGrounded;
	double jumVelocity{ 10.0f };
public:
	sf::Vector2f position{};
	/*const double marioW = 32.0f;
	const double marioH = 64.0f;*/

	// Functions
	void Begin();
	void Update(float deltaTime, Map& map);
	void Render(Renderer& renderer) const;
};

