#include "Cursor.h"

Cursor::Cursor(const sf::Vector2f & size) : AnimatedSprite(size)
{
	// setting up the animation and setting some default values
	spin.init(0, 0, 61, 50, 11, 0.2f);
	currentAnimation = &spin;
	frame = currentAnimation->getCurrentFrame();
	setTextureRect(frame);
	cursor_texture.loadFromFile("gfx/wheel_animation.png");
	setTexture(&cursor_texture);
	setSize(sf::Vector2f(40, 40));
}

Cursor::~Cursor()
{

}

void Cursor::update(float dt)
{
	// sets the sprites position to where the mouse is
	setPosition(position_x, position_y);

	elapsedTime += dt;

	// runs the animtion if it hasnt been paused
	if (moving)
	{
		if (elapsedTime >= currentAnimation->getAnimationTime())
		{
			currentAnimation->nextFrame();
			setTextureRect(currentAnimation->getCurrentFrame());
			elapsedTime = 0;
		}
	}
}

void Cursor::input(Input input)
{
	// sets the variables to where the mouse is
	position_x = input.getMouseX();
	position_y = input.getMouseY();
}
