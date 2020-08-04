#pragma once
#include "SFML\Graphics.hpp"
class Sprite : public sf::RectangleShape
{
public:
	Sprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Sprite();
	virtual void update(float dt) = 0;
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	void setAlive(bool x);
	bool getAlive();
	sf::Vector2f getVelocity();

	// collisions box functions
	sf::FloatRect getAABB();
	virtual void updateAABB();

protected:
	sf::Vector2f velocity;
	bool alive;
	float gravity;
	sf::FloatRect AABB;
};
