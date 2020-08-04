#include "Game.h"
#include "Menu.h"
#include "PauseScreen.h"
#include "ControlScreen.h"
void main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(1067, 600), "Pirate Rampage");
	Input input;
	Game game(&window, &input);
	Menu menu(&window, &input);
	ControlScreen controls(&window, &input);
	PauseScreen pause(&window, &input);

	sf::Clock clock;
	float deltaTime;
	srand(time(NULL));

	// declaring the game states and setting the default state
	enum GameState { Menu, ControlWindow, MainGame, PauseScreen };
	int currentState = 0;

	// runs while the game is running
	while (window.isOpen())
	{
		sf::Event event;
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			// code for handling envents such as keypresses
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0,
					event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				input.setMouseDown(event.key.code);
				break;
			case sf::Event::MouseButtonReleased:
				input.setMouseUp(event.key.code);
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// switch statement to control the screens and which screen it should be on
		switch (currentState)
		{
		case (GameState::Menu) :
			menu.handleInput(deltaTime);
			menu.update(deltaTime, input);
			menu.render();
			currentState = menu.getState();
			break;

		case (GameState::ControlWindow) :
			controls.handleInput(deltaTime);
			controls.update(deltaTime, input);
			controls.render();
			currentState = controls.getState();
			break;

		case (GameState::MainGame) :
			game.handleInput(deltaTime);
			game.update(deltaTime, input);
			game.render();
			currentState = game.getState();
			break;

		case (GameState::PauseScreen) :
			pause.handleInput(deltaTime);
			pause.update(deltaTime, input);
			pause.render();
			currentState = pause.getState();
			break;
		}
	}
}