#include "Game.h"


Game::Game(sf::RenderWindow* hwnd, Input* ccc)
{
	window = hwnd;

	// setting the backgrounds texture, position, velocity and size
	sky_texture.loadFromFile("gfx/sky.png");
	sky.setTexture(&sky_texture);
	sky.setSize(sf::Vector2f(2134, 600));
	sky.setPosition(0, 0);
	sky.setVelocity(-50, 0);

	waves_texture.loadFromFile("gfx/waves.png");
	waves.setTexture(&waves_texture);
	waves.setSize(sf::Vector2f(2134, 200));
	waves.setPosition(0, 320);
	waves.setVelocity(-30, 0);

	ship_texture.loadFromFile("gfx/ship.png");
	ship.setTexture(&ship_texture);
	ship.setSize(sf::Vector2f(1067, 600));
	ship.setPosition(0, 0);

	fade_texture.loadFromFile("gfx/fade.png");
	fade.setTexture(&fade_texture);
	fade.setSize(sf::Vector2f(1067, 600));
	fade.setPosition(0, 0);

	// setting up music and sound effects
	audio.addMusic("audio/background_music.wav", "music");
	audio.addSound("audio/hurt.wav", "damage");
	audio.addSound("audio/swing.flac", "swing");
	audio.addSound("audio/gameover_sound.wav", "game_over");

	// setting the players position
	player.setPosition(300, 500);

	// setting the enemies position
	enemy[0].setPosition(1, 305);
	enemy[1].setPosition(966, 305);
	enemy[2].setPosition(1, 505);
	enemy[3].setPosition(966, 505);

	// loads in the font
	font.loadFromFile("gfx/font.ttf");
	// sets the font for all the text and sets the colour
	for (int x = 0; x < 6; x++)
	{
		text[x].setFont(font);
		text[x].setFillColor(sf::Color::Red);
	}

	// setting the position and character size of each bit of text
	text[0].setPosition(600, 10);
	text[0].setCharacterSize(30);

	text[1].setPosition(760, 10);
	text[1].setCharacterSize(30);

	text[2].setPosition(100, 200);
	text[2].setCharacterSize(100);

	text[3].setPosition(150, 350);
	text[3].setCharacterSize(50);

	// setting up invisible boxes for the floor on different levels
	floor[0].setSize(sf::Vector2f(1067, 20));
	floor[0].setPosition(0, 200);
	floor[0].setFillColor(sf::Color::Red);

	floor[1].setSize(sf::Vector2f(1067, 20));
	floor[1].setPosition(0, 400);
	floor[1].setFillColor(sf::Color::Red);

	// setting health bar size and poisions
	health_bar[0].setSize(sf::Vector2f(100, 32));
	health_bar[0].setPosition(100, 10);

	health_bar[1].setSize(sf::Vector2f(100, 32));
	health_bar[1].setPosition(169, 10);

	health_bar[2].setSize(sf::Vector2f(100, 32));
	health_bar[2].setPosition(238, 10);

}
Game::~Game()
{
}

void Game::update(float dt, Input input)
{
	// sets mouse to invisable
	window->setMouseCursorVisible(false);
	// timer that increases with the time
	scoreTimer += dt;
	dropTimer += dt;

	if (!musicStart)
	{
		audio.playMusicbyName("music");
		musicStart = true;
	}

	// updates player, rain and enemies if the player hasnt died and game still running
	if (!gameOver)
	{
		sky.update(dt);
		waves.update(dt);
		player.update(dt);
		player.input(input);
		player.updateAABB();
		rain.update(dt);
		rain.spawn();
		gameOverSound = false;

		for (int x = 0; x < 4; x++)
		{
			enemy[x].update(dt);
			enemy[x].updateAABB();
			enemy[x].follow(&player);
		}
	}
	else
	{
		audio.stopAllMusic();
		if (!gameOverSound)
		{
			audio.playSoundbyName("game_over");
			gameOverSound = true;
		}
		// button to restart the game and reset values that need reset
		if (input.isKeyDown(sf::Keyboard::Return))
		{
			player.setPosition(300, 500);
			player.health = 3;
			score = 0;
			musicStart = false;
			enemy[0].setPosition(1, 305);
			enemy[1].setPosition(966, 305);
			enemy[2].setPosition(1, 505);
			enemy[3].setPosition(966, 505);
			for (int x = 0; x < 4; x++)
			{
				enemy[x].health = 2;
			}
			gameOver = false;
			input.setKeyUp(sf::Keyboard::Return);
		}
	}

	// checks if the player has died and changes the game to game over
	if (player.health == 0)
	{
		gameOver = true;
	}

	if (sky.getPosition().x <= -1067)
	{
		sky.setPosition(0, 0);
	}
	if (waves.getPosition().x <= -1067)
	{
		waves.setPosition(0, 320);
	}
	
	// loops through 4 times to check collision with each enemy and the player
	for (int x = 0; x < 4; x++)
	{
		// if the enemy collides with the player and player is attackin run collision response to take enemy health away and add score
		if ((checkCollision(&player, &enemy[x])) && (player.attacking == true))
		{
			enemy[x].collisionResponse2();
			player.setVelocity(0, player.getVelocity().x);
			audio.playSoundbyName("damage");
			if (scoreTimer > 1)
			{
				score++;
				scoreTimer = 0;
			}
		}
		// if enemy collides and player isnt attacking, make the enemy attack and player loses a life
		else if (checkCollision(&player, &enemy[x]))
		{
			enemy[x].collisionResponse();
			player.collisionResponse();
			collidedEnemy = x;
			audio.playSoundbyName("damage");
		}
	}

	// loops for each floor
		for (int x = 0; x < 2; x++)
		{
			if (checkFloorCollision(&floor[x], &player))
			{
				// if floor and player are colliding and s key is pressed make the player fall down to the next platform
				if (drop)
				{
					if (dropTimer > 0.5)
					{
						drop = false;
					}
				}
				else
				{
					if (input.isKeyDown(sf::Keyboard::S))
					{
						player.setPosition(player.getPosition().x, floor[x].getPosition().y - 85);
						player.falling = true;
						input.setKeyUp(sf::Keyboard::S);
						drop = true;
						dropTimer = 0;
					}
				}
			}
			if (player.falling)
			{
				// if player hits the floor when they are so far through it, it will teleport them onto of the platform to walk on and stop falling
				if ((checkFloorCollision(&floor[x], &player)) && ((floor[x].getPosition().y - player.getPosition().y) > 85))
				{
					if ((floor[x].getPosition().y - player.getPosition().y) > 85 && (floor[x].getPosition().y - player.getPosition().y) < 95)
					{
						player.falling = false;
						player.jumping = false;
						player.doubleJump = false;
						player.setPosition(player.getPosition().x, (floor[x].getPosition().y - 95));
					}
				}
			}
		}

	// runs player hitback code with the enemy that it has just collided with as a parameter
	player.hitback(&enemy[collidedEnemy]);

	// changes the game to paused if escape is pressed
	if (input.isKeyDown(sf::Keyboard::Escape))
	{
		input.setKeyUp(sf::Keyboard::Escape);
		pause = true;
	}

	// changes the size of the player depending on which animation is playing to make it the right scale
	if (player.attacking)
	{
		// allows swing sound effect to play 2 times as the player swings the sword twice
		swingTimer += dt;
		if (swingTimer <= 0.3)
		{
			audio.playSoundbyName("swing");
		}
		if (swingTimer >= 0.9)
		{
			audio.playSoundbyName("swing");
		}
		player.setSize(sf::Vector2f(140, 95));
	}
	else if (player.falling)
	{
		player.setSize(sf::Vector2f(100, 110));
	}
	else
	{
		swingTimer = 0;
		player.setSize(sf::Vector2f(100, 95));
	}

	// setting the text values to read on the screen
	text[0].setString("SCORE:");
	text[1].setString(std::to_string(score));
	text[2].setString("GAME OVER");
	text[3].setString("Press Enter To Restart");
}

void Game::handleInput(float dt)
{
}

void Game::render()
{
	beginDraw();
	// code for drawing all the objects on the screen
	window->draw(sky);
	window->draw(waves);
	rain.render(window);
	window->draw(ship);
	window->draw(player);
	for (int x = 0; x < 4; x++)
	{
		window->draw(enemy[x]);
	}
	window->draw(text[0]);
	window->draw(text[1]);
	// code for drawing the health bar depending on the players health
	if (player.health >= 1)
	{
		window->draw(health_bar[0]);
		if (player.health >= 2)
		{
			window->draw(health_bar[1]);
			if (player.health == 3)
			{
				window->draw(health_bar[2]);
			}
		}
	}
	if (gameOver)
	{
		window->draw(fade);
		window->draw(text[2]);
		window->draw(text[3]);
	}
	endDraw();
}

void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game::endDraw()
{
	window->display();
}

// choses which state the screen should be on and returns it to main
int Game::getState()
{
	if (pause)
	{
		pause = false;
		return 3;
	}
	else
	{
		return 2;
	}
}

// code to check if a sprite is colliding with another sprite if none of the conditions are met
// must be colliding and will return true
bool Game::checkCollision(Sprite* s1, Sprite* s2)
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

// code for specifically checking collisions between the player and the floors
bool Game::checkFloorCollision(sf::RectangleShape* s1, Sprite* s2)
{
	if (s1->getPosition().x + s1->getSize().x < s2->getAABB().left)
		return false;
	if (s1->getPosition().x > s2->getAABB().left + s2->getAABB().width)
		return false;
	if (s1->getPosition().y + s1->getSize().y < s2->getAABB().top)
		return false;
	if (s1->getPosition().y > s2->getAABB().top + s2->getAABB().height)
		return false;

	return true;
}

