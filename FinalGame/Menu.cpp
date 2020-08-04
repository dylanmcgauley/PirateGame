#include "Menu.h"


Menu::Menu(sf::RenderWindow* hwnd, Input* ccc)
{
	window = hwnd;

	// setting the backgrounds texture, position and size
	background_texture.loadFromFile("gfx/menu.png");
	background.setTexture(&background_texture);
	background.setSize(sf::Vector2f(1067, 600));
	background.setPosition(0, 0);

	// setting the texture, position and size for the start button
	start_texture[0].loadFromFile("gfx/start.png");
	start_texture[1].loadFromFile("gfx/start_selected.png");
	start_button.setSize(sf::Vector2f(300, 100));
	start_button.setPosition(100, 100);

	// setting the texture, position and size for the controls button
	controls_texture[0].loadFromFile("gfx/control.png");
	controls_texture[1].loadFromFile("gfx/control_selected.png");
	controls_button.setSize(sf::Vector2f(300, 100));
	controls_button.setPosition(100, 400);

	// setting up background music
	audio.addMusic("audio/menu_music.wav", "music");
}


Menu::~Menu()
{
}

void Menu::update(float dt, Input input)
{
	window->setMouseCursorVisible(false);
	// updating all of the collision boxes and other things that get updated
	start_button.updateAABB();
	controls_button.updateAABB();
	cursor.updateAABB();
	cursor.update(dt);
	cursor.input(input);

	if (!musicStart)
	{
		audio.playMusicbyName("music");
		musicStart = true;
	}
	
	// checks collision between the cursor and the start button
	if (checkCollision(&start_button, &cursor))
	{
		// starts the animation for the cursor and changes the button to its selected texture
		cursor.moving = true;
		start_button.setTexture(&start_texture[1]);
		// checks if the mouse button is clicked and if so changes the game state to game screen
		if (input.isMouseDown(sf::Mouse::Left))
		{
			input.setMouseUp(sf::Mouse::Left);
			gameStart = true;
		}
	}
	else
	{
		// resets the button texture to the unselected state
		start_button.setTexture(&start_texture[0]);
	}

	// checks collision between the cursor and the controls button
	if (checkCollision(&controls_button, &cursor))
	{
		// starts animation and changes to selected texture
		cursor.moving = true;
		controls_button.setTexture(&controls_texture[1]);
		// checks if mouse is clicked then changes state to controls screen if it is
		if (input.isMouseDown(sf::Mouse::Left))
		{
			input.setMouseUp(sf::Mouse::Left);
			controls = true;
		}
	}
	else
	{
		// resets the button texture
		controls_button.setTexture(&controls_texture[0]);
	}

	// stops animation is not colliding with anything
	if (!(checkCollision(&start_button, &cursor)) && !(checkCollision(&controls_button, &cursor)))
	{
		cursor.moving = false;
	}
}

void Menu::handleInput(float dt)
{
}

void Menu::render()
{
	beginDraw();
	// draws all the objects
	window->draw(background);
	window->draw(start_button);
	window->draw(controls_button);
	window->draw(cursor);
	endDraw();
}

void Menu::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Menu::endDraw()
{
	window->display();
}

bool Menu::checkCollision(Sprite* s1, Sprite* s2)
{
	if (s1->getAABB().left + s1->getAABB().width < s2->getAABB().left)
		return false;
	if (s1->getAABB().left > s2->getAABB().left + s2->getAABB().width)
		return false;
	if (s1->getAABB().top + s1->getAABB().height < s2->getAABB().top)
		return false;
	if (s1->getAABB().top > s2->getAABB().top + s2->getAABB().height)
		return false;

	return true;
}

// choses which state the screen should be on and returns it to main
int Menu::getState()
{
	if (gameStart)
	{
		audio.stopAllMusic();
		gameStart = false;
		return 2;
	}
	else if (controls)
	{
		controls = false;
		return 1;
	}
	else
	{
		return 0;
	}
}

