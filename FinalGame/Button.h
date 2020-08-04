#pragma once
#include "Sprite.h"

class Button : public Sprite
{
public:
	Button(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Button();

	void update(float dt);
};