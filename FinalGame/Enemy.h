#pragma once
#include "AnimatedSprite.h"
#include "Animation.h"
class Enemy : public AnimatedSprite
{
public:
	Enemy(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Enemy();

	// functions that will be used in the enemy class
	void update(float dt);
	void movement();
	void follow(Sprite* s1);
	void collisionResponse();
	void collisionResponse2();

	// public variables
	bool attacking;
	bool collided;
	bool respawn;
	float actionTimer;
	float actionTimer2;
	float healthTimer;
	float respawnTimer;
	int health;

protected:
	// protected variables
	Animation walk;
	Animation stand;
	Animation attack;
	Animation* currentAnimation;
	sf::Vector2f spawnPoints[6];
	sf::Texture enemy_sheet;
	int random;
};

