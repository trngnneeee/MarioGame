#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Camera.h"
#include "GameState.h"

extern Camera camera;

class Map;
class PowerUpMushroom;
class InvicibleStar;

void Begin(sf::RenderWindow& window);
void BeginMenu(sf::RenderWindow& window);

void UpdateMap(float deltaTime);
void UpdateCamera();
void UpdateMario(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushrooms, std::vector<InvicibleStar*>& stars, GameState& gamestate);
void UpdateGoomba(float deltaTime, const Map& map);
void UpdateKoopa(float deltaTime, const Map& map);
void UpdateMushroom(float deltaTime, const Map& map);
void UpdateStar(float deltaTime, const Map& map);
void UpdateCoin(float deltaTime);
void UpdateGameTime(float deltaTime);
void UpdateGameState(GameState& gameState, sf::RenderWindow& window);

void Update(float deltaTime, GameState& gameState, sf::RenderWindow& window);

void Render(sf::RenderWindow& window);
void RenderUI(sf::RenderWindow& window, float deltaTime);
void RenderMenu(sf::RenderWindow& window);

void Reset();
void handleGameOver();