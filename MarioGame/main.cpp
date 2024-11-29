#include "Game.h"
#include "GameState.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario Game");
	sf::Clock deltaClock;
	window.setFramerateLimit(60);

	GameState gameState = GameState::Menu;
	BeginMenu(window);

	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();
		if (deltaTime > 1.f / 30.0f) continue;

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (gameState == GameState::Playing)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					window.close();
			}
			if (gameState == GameState::Menu)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
				{
					window.setView(window.getDefaultView());
					BeginGame(window);
					gameState = GameState::Playing;
				}
			}			
		}

		window.clear();

		if (gameState == GameState::Menu)
		{
			RenderMenu(window);
		}
		else if (gameState == GameState::Playing)
		{			
			UpdateGame(deltaTime, gameState, window);
			
			RenderGame(window);
			
			RenderUI(window, deltaTime);

			window.display();
		}
		else if (gameState == GameState::GameOver)
		{
			gameState = GameState::Menu;
		}
	}
	return 0;
}