#pragma once
#include "Sprite.h"
#include "Rain.h"
#include <time.h>
#include <math.h>
#include <vector>
class RainManager :
	public Sprite
{
public:
	RainManager();
	~RainManager();
	void spawn();
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);

private:
	std::vector<Rain> rainDrops;
	sf::Vector2f spawnPoint;
	sf::Texture texture;
	int random;
	int random2;
};

