#pragma once
#include <SFML/Graphics.hpp>
#include "input.h"
#include "Background.h"
#include "Button.h"
#include "Cursor.h"
class ControlScreen
{
public:
	// declaring all the variables, sprites and textures that will be needed on this screen
	Background background;
	sf::Texture background_texture;

	Button menu_button;
	sf::Texture button_texture[2];

	Cursor cursor;

	ControlScreen(sf::RenderWindow* hwnd, Input* ccc);
	~ControlScreen();

	// all of the functions used in this class
	void handleInput(float dt);
	void update(float dt, Input input);
	bool checkCollision(Sprite* x, Sprite* y);
	void render();
	int getState();
private:
	// private variables
	bool menu = false;
	sf::RenderWindow* window;
	void beginDraw();
	void endDraw();
};

