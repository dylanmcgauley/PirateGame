#pragma once
#include "Sprite.h"
class Health : public Sprite
{
public:
	Health(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Health();
	void update(float dt);

	sf::Texture health_texture;
};

