#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Camera.h"

extern Camera camera;

void Begin(const sf::Window& window);
void Update(float deltaTime, bool& isDead);
void Render(sf::RenderWindow& window);
void Reset();