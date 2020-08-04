#pragma once
#include "AnimatedSprite.h"
#include "Animation.h"
#include "input.h"

class Cursor : public AnimatedSprite
{
public:
	Cursor(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Cursor();

	// variables for mouse cursor texture
	int position_x;
	int position_y;
	sf::Texture cursor_texture;

	bool moving = false;

	// functions
	void update(float dt);
	void input(Input input);

protected:
	// animation
	Animation spin;
	Animation* currentAnimation;
};