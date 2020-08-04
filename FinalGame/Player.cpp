#include "Player.h"



Player::Player(const sf::Vector2f & size) : AnimatedSprite(size)
{
	// setting up the animations and setting the current animation
	stand.init(0, 96, 104, 93, 21, 0.05f);
	walk.init(0, 0, 109, 95, 21, 0.03f);
	jump.init(0, 191, 106, 110, 11, 0.04f);
	attack.init(0, 305, 143, 95, 21, 0.03f);
	currentAnimation = &stand;
	frame = currentAnimation->getCurrentFrame();
	setTextureRect(frame);

	// setting some default values for the player
	character_sheet.loadFromFile("gfx/character_sheet.png");
	setTexture(&character_sheet);
	scale = 200.f;
	gravity = 8.0f*scale;
	falling = true;
	health = 3;
}


Player::~Player()
{
}

void Player::update(float dt)
{
	// starting the timers
	elapsedTime += dt;
	actionTimer += dt;
	healthTimer += dt;

	// plays the animation unless they have been stopped
	if (!stopAnimation)
	{
		if (elapsedTime >= currentAnimation->getAnimationTime())
		{
			currentAnimation->nextFrame();
			setTextureRect(currentAnimation->getCurrentFrame());
			elapsedTime = 0;
		}
	}

	// if the player is falling this will apply a downwards gravity and change the animation to jumping
	if (falling)
	{
		velocity.y += (gravity)*dt;
		move(velocity*dt);
		currentAnimation = &jump;
		// if they fall to the bottom of the screen this will stop them from falling any further
		if (getPosition().y > 505)
		{
			falling = false;
			jumping = false;
			doubleJump = false;
			setPosition(getPosition().x, 505);
		}
	}
	else
	{
		velocity.y = 0;
		// code for moving the player based on their velocity
		move(velocity*dt);
	}

	// this stops the player from going off the side of the screen
	if (getPosition().x < 0)
	{
		setPosition(0, getPosition().y);
	}
	else if (getPosition().x > 967)
	{
		setPosition(967, getPosition().y);
	}
}

void Player::input(Input input)
{
	// animaiton will pause after 0.42 seconds if jumping or double jumping
	if (doubleJump)
	{
		if (actionTimer >= 0.42)
		{
			stopAnimation = true;
		}
	}
	else if (jumping)
	{
		if (actionTimer >= 0.42)
		{
			stopAnimation = true;
		}
		// if the player is jumping and presses space again it will start a double jump
		if ((actionTimer > 0.3) && (input.isKeyDown(sf::Keyboard::Space)))
		{
			velocity.y = -3.f*scale;
			doubleJump = true;
			input.setKeyUp(sf::Keyboard::Space);
		}
	}
	else
	{
		// if not jumping resume the animation and check to see when space is pressed to jump again
		stopAnimation = false;
		if (input.isKeyDown(sf::Keyboard::Space))
		{
			// setting upwards velocity after jumping and applying gravity
			velocity.y = -3.f*scale;
			falling = true;
			jumping = true;
			actionTimer = 0;
			input.setKeyUp(sf::Keyboard::Space);
		}
	}
	// checks to see if E is pressed and if it is the player will start the attacking animation and set the player to attacking
	if (input.isKeyDown(sf::Keyboard::E))
	{
		if (actionTimer >= 1.1)
		{
			attacking = true;
			actionTimer = 0;
		}
		input.setKeyUp(sf::Keyboard::E);
	}
	if (collided)
	{
		// allows the player to bounce back after being hit
		if (actionTimer > 0.6)
		{
			collided = false;
		}
	}
	// if attacking changes the animation and only attacks for 1 second
	else if (attacking)
	{
		currentAnimation = &attack;
		if (actionTimer > 1)
		{
			attacking = false;
			actionTimer = 0;
		}
	}
	// code bellow for moving the player back and forward as well as flipping the player if necessary
	else if (input.isKeyDown(sf::Keyboard::A))
	{
		velocity.x = -100;
		if (!falling)
		{
			currentAnimation = &walk;
		}
		walk.flipped = true;
		stand.flipped = true;
		jump.flipped = true;
		attack.flipped = true;
		input.setKeyUp(sf::Keyboard::A);
	}
	else if (input.isKeyDown(sf::Keyboard::D))
	{
		velocity.x = 100;
		if (!falling)
		{
			currentAnimation = &walk;
		}
		walk.flipped = false;
		stand.flipped = false;
		jump.flipped = false;
		attack.flipped = false;
		input.setKeyUp(sf::Keyboard::D);
	}
	else
	{
		// if the player isnt pressing any buttons stop the player and play standing animation
		velocity.x = 0;
		if (!falling && !attacking)
		{
			currentAnimation = &stand;
		}
	}
}

// collision response for if the enemy hits the player
void Player::collisionResponse()
{
	if (healthTimer > 1)
	{
		health--;
		collided = true;
		velocity.y = -2.5f*scale;
		falling = true;
		jumping = true;
		actionTimer = 0;
		healthTimer = 0;
	}
}

// checks to see which enemy hit the player and hits the player back depending on which side the enemy was on
void Player::hitback(Sprite* s1)
{
	if (collided)
	{
		if (s1->getPosition().x > getPosition().x)
		{
			velocity.x = -200;
		}
		else
		{
			velocity.x = 200;
		}
	}
}