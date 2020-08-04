#include "ControlScreen.h"


ControlScreen::ControlScreen(sf::RenderWindow* hwnd, Input* ccc)
{
	window = hwnd;

	// setting up the background texture, size and position
	background_texture.loadFromFile("gfx/controls.png");
	background.setTexture(&background_texture);
	background.setSize(sf::Vector2f(1067, 600));
	background.setPosition(0, 0);

	// setting up the buttons textures and positions
	button_texture[0].loadFromFile("gfx/back.png");
	button_texture[1].loadFromFile("gfx/back_selected.png");
	menu_button.setSize(sf::Vector2f(300, 100));
	menu_button.setPosition(383, 500);
}


ControlScreen::~ControlScreen()
{
}

void ControlScreen::update(float dt, Input input)
{
	window->setMouseCursorVisible(false);
	// updating all of the collision boxes and other things that get updated
	menu_button.updateAABB();
	cursor.updateAABB();
	cursor.update(dt);
	cursor.input(input);

	// checks to see if the mouse cursor and the button is colliding
	if (checkCollision(&menu_button, &cursor))
	{
		// starts the cursor animation and changes the buttons texture to selected
		cursor.moving = true;
		menu_button.setTexture(&button_texture[1]);
		// changes the screen if mouse button is clicked
		if (input.isMouseDown(sf::Mouse::Left))
		{
			input.setMouseUp(sf::Mouse::Left);
			menu = true;
		}
	}
	else
	{
		cursor.moving = false;
		menu_button.setTexture(&button_texture[0]);
	}
}

void ControlScreen::handleInput(float dt)
{
}

void ControlScreen::render()
{
	beginDraw();
	// renders everything on the screen
	window->draw(background);
	window->draw(menu_button);
	window->draw(cursor);
	endDraw();
}

void ControlScreen::beginDraw()
{
	window->clear(sf::Color::Black);
}

void ControlScreen::endDraw()
{
	window->display();
}

bool ControlScreen::checkCollision(Sprite* s1, Sprite* s2)
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
int ControlScreen::getState()
{
	if (menu)
	{
		menu = false;
		return 0;
	}
	else
	{
		return 1;
	}
}


