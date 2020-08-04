#include "Health.h"



Health::Health(const sf::Vector2f & size) : Sprite(size)
{
	health_texture.loadFromFile("gfx/health.png");
	setTexture(&health_texture);
}


Health::~Health()
{
}

void Health::update(float dt)
{

}
