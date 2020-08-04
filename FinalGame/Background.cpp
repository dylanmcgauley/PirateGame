#include "Background.h"


Background::Background(const sf::Vector2f & size) : Sprite(size)
{

}

Background::~Background()
{

}

void Background::update(float dt)
{
	// moves the background using its velocity
	move(velocity*dt);
}