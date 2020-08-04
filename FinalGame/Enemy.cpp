#include "Enemy.h"



Enemy::Enemy(const sf::Vector2f & size) : AnimatedSprite(size)
{
	// setting up the animations and setting the current animation
	stand.init(0, 96, 104, 93, 21, 0.05f);
	walk.init(0, 0, 109, 95, 21, 0.03f);
	attack.init(0, 305, 143, 95, 21, 0.03f);
	currentAnimation = &stand;
	frame = currentAnimation->getCurrentFrame();
	setTextureRect(frame);

	// setting the enemy spawn positions and the default vales for the enemy
	enemy_sheet.loadFromFile("gfx/enemy_sheet.png");
	spawnPoints[0] = sf::Vector2f(-400, 505);
	spawnPoints[1] = sf::Vector2f(1400, 505);
	spawnPoints[2] = sf::Vector2f(-400, 305);
	spawnPoints[3] = sf::Vector2f(1400, 305);
	spawnPoints[4] = sf::Vector2f(-400, 105);
	spawnPoints[5] = sf::Vector2f(1400, 105);
	setTexture(&enemy_sheet);
	setSize(sf::Vector2f(100, 95));
	health = 2;
}


Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	// starting the timers
	elapsedTime += dt;
	actionTimer += dt;
	actionTimer2 += dt;
	healthTimer += dt;
	respawnTimer += dt;
	// moving the enemies at their velocities
	move(velocity*dt);
	updateAABB();

	random = rand() % 6;

	// plays the animation
	if (elapsedTime >= currentAnimation->getAnimationTime())
	{
		currentAnimation->nextFrame();
		setTextureRect(currentAnimation->getCurrentFrame());
		elapsedTime = 0;
	}

	// if an enemy dies this will start the restart code
	if ((health == 0) && (!respawn))
	{
		respawn = true;
		respawnTimer = 0;
	}

	// gives the dead enemy a random new spawn point and resets their health
	if (respawn)
	{
		setPosition(spawnPoints[random]);
		if (respawnTimer >= 2)
		{
			health = 2;
			respawn = false;
		}
	}

	// changes the enemies size if attacking due to stretched textures
	if (attacking)
	{
		setSize(sf::Vector2f(140, 95));
		currentAnimation = &attack;
		// allows the enemy to attack for 0.6 seconds before moving off again
		if (actionTimer2 > 0.6)
		{
			attacking = false;
			if (walk.flipped == true)
			{
				velocity.x = -90;
			}
			else
			{
				velocity.x = 90;
			}
			actionTimer2 = 0;
		}
	}
	
	// sets the animation for walking and which direction they should be facing based on velocity
	if ((velocity.x > 0))
	{
		setSize(sf::Vector2f(100, 95));
		currentAnimation = &walk;
		walk.flipped = false;
		stand.flipped = false;
		attack.flipped = false;
	}
	else if ((velocity.x < 0))
	{
		setSize(sf::Vector2f(100, 95));
		currentAnimation = &walk;
		walk.flipped = true;
		stand.flipped = true;
		attack.flipped = true;
	}
	else
	{
		// sets their animation to standing if not doing anything else
		if (!attacking)
		{
			setSize(sf::Vector2f(100, 95));
			currentAnimation = &stand;
		}
	}
}

// function for AI movement
void Enemy::movement()
{
	// if they have health they will be on the screen
	if (health != 0)
	{
		// moves enemy from one side of the screen to the other with a 2 second delay at each side of the screen
		if (getPosition().x <= 0)
		{
			velocity.x = 0;
			actionTimer = 0;
			setPosition(1, getPosition().y);
		}
		else if (getPosition().x >= 967)
		{
			velocity.x = 0;
			actionTimer = 0;
			setPosition(966, getPosition().y);
		}

		if ((getPosition().x == 1) && (actionTimer > 2))
		{
			actionTimer = 0;
			velocity.x = 90;
		}
		else if ((getPosition().x == 966) && (actionTimer > 2))
		{
			actionTimer = 0;
			velocity.x = -90;
		}
	}
}

void Enemy::follow(Sprite* s1)
{
	if (collided)
	{
		// checks to see what side of the player the enemy is at after colliding to see what direction they should run away
		if (s1->getPosition().x > getPosition().x)
		{
			velocity.x = -200;
		}
		else
		{
			velocity.x = 200;
		}
		if (healthTimer > 0.6)
		{
			collided = false;
		}
	}
	// checks to see if the player is on the same level as the enemy and withing a certain number of pixels away, follows the player if condition is true
	else if ((s1->getPosition().x - getPosition().x > -400) && (s1->getPosition().x - getPosition().x < 400) && (s1->getPosition().y == getPosition().y) && (!attacking))
	{
		if (s1->getPosition().x > getPosition().x)
		{
			velocity.x = 90;
		}
		else if (s1->getPosition().x == getPosition().x)
		{
			velocity.x = 0;
		}
		else
		{
			velocity.x = -90;
		}
	}
	else
	{
		// if the conditions are not met the player will go back to its default movement path
		movement();
	}
}

// collision response for if colliding with player and the player is not attacking
void Enemy::collisionResponse()
{
	velocity.x = 0;
	attacking = true;
	actionTimer2 = 0;
}

// collision response for if colliding with player and the player is attacking
void Enemy::collisionResponse2()
{
	if (healthTimer > 1)
	{
		health--;				
		collided = true;
		healthTimer = 0;
	}
}

