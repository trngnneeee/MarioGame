#include "MarioGame.h"
#include "GameState.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario Game");
	sf::Clock deltaClock;
	window.setFramerateLimit(60);

	MarioGame game;
	GameState gameState = GameState::Menu;
	game.MenuBegin(window);


	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();
		if (deltaTime > 1.f / 30.0f) continue;

		game.Event(window, gameState);

		window.clear();

		game.Update(deltaTime, gameState, window);

		game.Render(window, gameState);

		window.display();
	}
	return 0;
}