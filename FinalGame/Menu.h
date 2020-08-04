#pragma once
#include <SFML/Graphics.hpp>
#include "input.h"
#include "Background.h"
#include "AudioManager.h"
#include "Button.h"
#include "Cursor.h"
class Menu
{
public:
	// declaring all the variables, sprites and textures that will be needed on this screen
	Background background;
	sf::Texture background_texture;

	Button start_button;
	Button controls_button;
	sf::Texture start_texture[2];
	sf::Texture controls_texture[2];

	Cursor cursor;

	AudioManager audio;

	Menu(sf::RenderWindow* hwnd, Input* ccc);
	~Menu();

	// all of the functions used in this class
	void handleInput(float dt);
	void update(float dt, Input input);
	bool checkCollision(Sprite* x, Sprite* y);
	void render();
	int getState();
private:
	// private variables
	bool gameStart = false;
	bool controls = false;
	bool musicStart = false;
	sf::RenderWindow* window;
	void beginDraw();
	void endDraw();
};

