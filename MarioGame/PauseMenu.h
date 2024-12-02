#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class PauseMenu {
private:
    sf::Font font;
    sf::Text resumeText;
    sf::Text quitText;

public:
    void Initialize(sf::RenderWindow& window);
    void HandleInput(const sf::Event& event, GameState& gameState, sf::RenderWindow& window);
    void Update(float deltaTime, sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);
    void UpdateTextPositions(sf::RenderWindow& window);
};
