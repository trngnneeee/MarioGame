#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Camera.h"
#include "GameState.h"

extern Camera camera;

void Begin(sf::RenderWindow& window);
void BeginMenu(sf::RenderWindow& window);

void Update(float deltaTime, bool& isDead);

void Render(sf::RenderWindow& window);
void RenderUI(sf::RenderWindow& window, float deltaTime);
void RenderMenu(sf::RenderWindow& window);

void HandleDead(float deltaTime);

bool isEnd();
void handleEnd();

void Reset();