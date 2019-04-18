#include <iostream>
#include "MooCows.h"
#include "Bottles.h"
#include "Boris.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FARTHEST_LEFT =-7;
const int FARTHEST_RIGHT = WINDOW_WIDTH - 120;

Boris::Boris()
{

}

Boris::Boris(Texture &bossTexture)
{
	boris.setPosition(150, 100);
	boris.setTexture(bossTexture);
	health = 25;
	direction = false;
}

FloatRect Boris::getGlobalBounds()
{
	return boris.getGlobalBounds();
}

Sprite Boris::getSprite()
{
	return boris;
}

int Boris::getHealth()
{
	return health;
}

void Boris::setDeepFried(Texture &deepFried)
{
	boris.setTexture(deepFried);
}

void Boris::setFrames(int frames)
{
	framesTilFire = frames;
}

void Boris::setMovement(float movement)
{
	speed = movement;
}

void Boris::updatePos()
{
	
	if (direction)
		boris.move(5, 0);
	else
		boris.move(-5, 0);

	Vector2f borisPos = boris.getPosition();
	if (borisPos.x <= FARTHEST_LEFT)
	{
		direction = true;
	}
	else if (borisPos.x >= FARTHEST_RIGHT)
	{
		direction = false;
	}
}

void Boris::drawBoris(RenderWindow &win)
{
	win.draw(boris);
}

void Boris::throwMooCows(int frames, MooCows &trueDeath)
{
	if (frames == 0)
	{
 		trueDeath.addMooCow(boris.getPosition());
	}
	if (!trueDeath.getMooCows().empty())
	{
		trueDeath.updatePos();
	}
}

bool Boris::checkBounds(Bottles &bottles)
{
	list<Bottle>::iterator iterBottle = bottles.getBottles().begin();
	list<Bottle>::iterator bottleEnd = bottles.getBottles().end();
	FloatRect bottleBounds, enemyBounds;
	bool hit = false;
	if (!bottles.getBottles().empty())
	{
		for (iterBottle; iterBottle != bottleEnd && !hit; )
		{
			enemyBounds = getGlobalBounds();
			bottleBounds = iterBottle->getGlobalBounds();
			
			if (bottleBounds.intersects(enemyBounds))
			{
				iterBottle = bottles.getBottles().erase(iterBottle);
				health--;
				hit = true;
			}
			else
			{
				iterBottle++;
			}
		}
	}
	return hit;
}