#pragma once
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Input.h"
class Player : public AnimatedSprite
{
public:
	Player(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Player();

	// functions that will be used in the player class
	void update(float dt);
	void input(Input input);
	void collisionResponse();
	void hitback(Sprite* s1);

	// public variables
	bool falling;
	bool collided;
	float scale;
	float actionTimer;
	float healthTimer;
	int health;
	bool jumping;
	bool doubleJump;
	bool attacking;
	bool stopAnimation;

protected:
	// protected variables
	Animation walk;
	Animation stand;
	Animation jump;
	Animation attack;
	Animation* currentAnimation;
	sf::Texture character_sheet;
};

