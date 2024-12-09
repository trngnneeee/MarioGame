#include "MarioGame.h"
#include "GameState.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario Game");

	// Icon app 
	sf::Image Icon;
	Icon.loadFromFile("./resources/textures/Mario/marioHead.png");
	window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
	window.setFramerateLimit(60);

	sf::Clock deltaClock;
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