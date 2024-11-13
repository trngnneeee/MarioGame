#include "Game.h"
#include "Camera.h"
#include "GameState.h"
#include "Menu.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario Game");
	sf::Clock deltaClock;

	Menu menu;
	menu.Begin(window);

	window.setFramerateLimit(60);

	GameState gameState = GameState::Menu;

	while (window.isOpen())
	{
		// Use deltaTime to make movement and animations frame rate independent, not fix the velocity 
		float deltaTime = deltaClock.restart().asSeconds();
		if (deltaTime > 1.f / 30.0f) continue;

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (gameState == GameState::Menu)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
				{
					gameState = GameState::Playing;
					Begin(window);
				}
			}
			else if (gameState == GameState::Playing)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					window.close();
			}
			
		}
		if (gameState == GameState::Menu)
		{
			menu.Draw(window);			
		}
		else if (gameState == GameState::Playing)
		{
			bool isDead = false;
			// Setup camera consiquently view to mario
			window.setView(camera.GetView(window.getSize()));
			Update(deltaTime, isDead);
			Render(window);
			window.display();
			if (isDead)
			{
				Reset();
				window.setView(window.getDefaultView());
				gameState = GameState::GameOver;
			}
		}
		else if (gameState == GameState::GameOver)
		{
			gameState = GameState::Menu;
		}
	}
	return 0;
}