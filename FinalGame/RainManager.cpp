#include "RainManager.h"
RainManager::RainManager()
{
	spawnPoint = sf::Vector2f(350, 250);
	texture.loadFromFile("gfx/rain.png");
	// sets up 50 rain drops
	for (int x = 0; x < 50; x++)
	{
		rainDrops.push_back(Rain());
		rainDrops[x].setAlive(false);
		rainDrops[x].setTexture(&texture);
		rainDrops[x].setSize(sf::Vector2f(28, 58));
	}
}
RainManager::~RainManager()
{
}
void RainManager::update(float dt)
{
	// call update on all ALIVE balls
	for (int x = 0; x < rainDrops.size(); x++)
	{
		if (rainDrops[x].getAlive())
		{
			rainDrops[x].update(dt);
		}
	}
	deathCheck();
}
// Spawn new rain drop
// Find a dead rain drop, make alive, move to a random spawn point, give random velocity and random size
void RainManager::spawn()
{
	int sizeRand;
	for (int x = 0; x < rainDrops.size(); x++)
	{
		if (!rainDrops[x].getAlive())
		{
			rainDrops[x].setAlive(true);
			rainDrops[x].setVelocity(-(rand() % 400 + 400), rand() % 400 + 400);
			spawnPoint = sf::Vector2f((rand() % 300) + (x * 50), -20);
			sizeRand = rand() % 30;
			rainDrops[x].setSize(sf::Vector2f(sizeRand, sizeRand));
			rainDrops[x].setPosition(spawnPoint);
			return;
		}
	}
}

// Check all ALIVE rain drops to see if outside screen/range, if so make dead
void RainManager::deathCheck()
{
	for (int x = 0; x < rainDrops.size(); x++)
	{
		if (rainDrops[x].getAlive())
		{
			if (rainDrops[x].getPosition().y > 610)
			{
				rainDrops[x].setAlive(false);
			}
		}
	}
}
// Render all alive rain drops
void RainManager::render(sf::RenderWindow* window)
{
	for (int x = 0; x < rainDrops.size(); x++)
	{
		if (rainDrops[x].getAlive())
		{
			window->draw(rainDrops[x]);
		}
	}
}