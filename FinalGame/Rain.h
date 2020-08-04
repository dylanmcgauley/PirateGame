#pragma once
#include "Sprite.h"
class Rain : public Sprite
{
public:
	Rain();
	~Rain();

	void update(float dt);
};

