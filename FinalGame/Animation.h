#pragma once
#include "SFML\Graphics.hpp"
#include "AnimatedSprite.h"
class Animation : public AnimatedSprite
{
public:
	Animation();
	~Animation();
	void init(int left, int top, int width, int height, int frames, float speed);
	sf::IntRect getCurrentFrame();
	float getAnimationTime() { return animationSpeed; };
	void nextFrame();
	bool flipped;
protected:
	sf::IntRect frame;
	int numberOfFrames;
	float animationSpeed;
	int currentFrame;
};