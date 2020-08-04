#include "PauseScreen.h"



PauseScreen::PauseScreen(sf::RenderWindow* hwnd, Input* ccc)
{
	window = hwnd;

	// setting the backgrounds texture, position and size
	background_texture.loadFromFile("gfx/pause.png");
	background.setTexture(&background_texture);
	background.setSize(sf::Vector2f(1067, 600));
	background.setPosition(0, 0);

	// setting the texture, position and size for the resume button
	game_texture[0].loadFromFile("gfx/resume.png");
	game_texture[1].loadFromFile("gfx/resume_selected.png");
	game_button.setSize(sf::Vector2f(300, 100));
	game_button.setPosition(383, 500);
}


PauseScreen::~PauseScreen()
{
}

void PauseScreen::update(float dt, Input input)
{
	window->setMouseCursorVisible(false);
	// updating the collision boxes and cursor
	game_button.updateAABB();
	cursor.updateAABB();
	cursor.update(dt);
	cursor.input(input);

	// check to see if the cursor collides with the resume button
	if (checkCollision(&game_button, &cursor))
	{
		// starts the animation and changes the button to the selected texture
		cursor.moving = true;
		game_button.setTexture(&game_texture[1]);
		// checks to see if the mouse is clicked and if it is it switches the state to game
		if (input.isMouseDown(sf::Mouse::Left))
		{
			input.setMouseUp(sf::Mouse::Left);
			gameon = true;
		}
	}
	else
	{
		// stops animation if not colliding and resets the texture of the button
		cursor.moving = false;
		game_button.setTexture(&game_texture[0]);
	}
}

void PauseScreen::handleInput(float dt)
{
}

void PauseScreen::render()
{
	beginDraw();
	// renders all the objects
	window->draw(background);
	window->draw(game_button);
	window->draw(cursor);
	endDraw();
}

void PauseScreen::beginDraw()
{
	window->clear(sf::Color::Black);
}

void PauseScreen::endDraw()
{
	window->display();
}

bool PauseScreen::checkCollision(Sprite* s1, Sprite* s2)
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
int PauseScreen::getState()
{
	if (gameon)
	{
		gameon = false;
		return 2;
	}
	else
	{
		return 3;
	}
}

