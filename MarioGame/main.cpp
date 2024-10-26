#include "Game.h"
#include "Camera.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario Game");
	sf::Clock deltaClock;

	window.setFramerateLimit(60);
	Begin(window);
	while (window.isOpen())
	{
		// Use deltaTime to make movement and animations frame rate independent, not fix the velocity 
		float deltaTime = deltaClock.restart().asSeconds();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
			
		}
		// Setup camera, which use to fix the scale of render window
		window.setView(camera.GetView(window.getSize()));
			
		Update(deltaTime);

		window.clear(sf::Color::Black);

		Render(window);

		window.display();
	}
	return 0;
}