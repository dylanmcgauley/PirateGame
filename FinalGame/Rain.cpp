#include "Rain.h"



Rain::Rain()
{
}


Rain::~Rain()
{
}

void Rain::update(float dt)
{
	// moves the rain using their velocity
	move(velocity*dt);
}
