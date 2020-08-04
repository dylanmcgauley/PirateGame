#include "Sprite.h"
Sprite::~Sprite()
{}
Sprite::Sprite(const sf::Vector2f & size) : RectangleShape(size)
{
}
void Sprite::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}
void Sprite::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}
void Sprite::setAlive(bool x)
{
	alive = x;
}
bool Sprite::getAlive()
{
	return alive;
}
sf::Vector2f Sprite::getVelocity()
{
	return velocity;
}

sf::FloatRect Sprite::getAABB()
{
	return AABB;
}
void Sprite::updateAABB()
{
	// Axis Aligned Bounding Box, based on sprite size and position.
	// Shape could be smaller/larger and offset if required.
	// Can be overwritten by child classes
	AABB.left = getPosition().x;
	AABB.top = getPosition().y;
	AABB.width = getSize().x;
	AABB.height = getSize().y;
}
