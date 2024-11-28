#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Camera.h"
#include "GameState.h"

extern Camera camera;

class Map;
class PowerUpMushroom;
class InvicibleStar;

/// Begin
void BeginGame(sf::RenderWindow& window);

void BeginMap(
	sf::Vector2f& marioPosition,
	sf::Vector2f& winPosition,
	std::vector<sf::Vector2f>& goombasPosition,
	std::vector<sf::Vector2f>& koopaPosition,
	std::vector<sf::Vector2f>& coinPosition
);

void BeginMenu(sf::RenderWindow& window);
void BeginMario(sf::Vector2f marioPosition);
void BeginGoomba(std::vector<sf::Vector2f> goombasPosition);
void BeginKoopa(std::vector<sf::Vector2f> koopaPosition);
void BeginCoin(std::vector<sf::Vector2f> coinPosition);
void BeginBackground(const float& zoomLevel, const Map& map);
void BeginMusic();
void BeginGameTime();


/// Update
void UpdateGame(float deltaTime, GameState& gameState, sf::RenderWindow& window);

bool UpdateMapTransition(float deltaTime);
void UpdateMap(float deltaTime);
void UpdateCamera();
void UpdateMario(float deltaTime, Map& map, std::vector<std::unique_ptr<PowerUpMushroom>>& mushrooms, std::vector<std::unique_ptr<InvicibleStar>>& stars, GameState& gamestate);
void UpdateGoomba(float deltaTime, const Map& map);
void UpdateKoopa(float deltaTime, const Map& map);
void UpdateMushroom(float deltaTime, const Map& map);
void UpdateStar(float deltaTime, const Map& map);
void UpdateCoin(float deltaTime);
void UpdateGameTime(float deltaTime);
void UpdateGameState(GameState& gameState, sf::RenderWindow& window);
void handleWining();

/// Render
void RenderGame(sf::RenderWindow& window);

void RenderMapTransition(sf::RenderWindow& window);
void RenderBackground(sf::RenderWindow& window);
void RenderMushroom(sf::RenderWindow& window);
void RenderStar(sf::RenderWindow& window);
void RenderMap(sf::RenderWindow& window);
void RenderMario(sf::RenderWindow& window);
void RenderGoomba(sf::RenderWindow& window);
void RenderKoopa(sf::RenderWindow& window);
void RenderCoin(sf::RenderWindow& window);

void RenderUI(sf::RenderWindow& window, float deltaTime);
void RenderMenu(sf::RenderWindow& window);

void ResetGame();
