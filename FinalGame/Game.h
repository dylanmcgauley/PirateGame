#pragma once
#include <SFML/Graphics.hpp>
#include "input.h"
#include "Background.h"
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include "RainManager.h"
#include "AudioManager.h"
#include "Health.h"
#include "Button.h"
class Game {
public:

	// declaring all the variables, sprites and textures that will be needed on this screen
	Background sky;
	Background waves;
	Background ship;
	Background fade;
	sf::Texture sky_texture;
	sf::Texture waves_texture;
	sf::Texture ship_texture;
	sf::Texture fade_texture;

	Player player;

	Enemy enemy[4];

	Health health_bar[3];

	RainManager rain;

	AudioManager audio;

	sf::RectangleShape floor[2];

	sf::Font font;
	sf::Text text[4];

	Game(sf::RenderWindow* hwnd, Input* ccc);
	~Game();
	// declaring functions that will be used in the game class
	void handleInput(float dt);
	void update(float dt, Input input);
	void render();
	int getState();
	bool checkCollision(Sprite* x, Sprite* y);
	bool checkFloorCollision(sf::RectangleShape* x, Sprite* y);
private:
	// private variables and functions
	float spawnTimer;
	float scoreTimer;
	float dropTimer;
	float swingTimer;
	int collidedEnemy;
	int score;
	bool gameOver = false;
	bool drop = false;
	bool musicStart = false;
	bool gameOverSound = false;
	bool pause = false;
	sf::RenderWindow* window;
	void beginDraw();
	void endDraw();
};