#pragma once
#include "Sprite.h"

class Background : public Sprite
{
public:
	Background(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Background();

	void update(float dt);
};