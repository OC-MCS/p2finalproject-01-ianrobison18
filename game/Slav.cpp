#include <iostream>
#include <list>
#include "Slav.h"
#include "MooCow.h"
#include "MooCows.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

Slav::Slav()
{

}

Slav::Slav(Sprite &slav)
{
	this->slav = slav;
}

FloatRect Slav::getGlobalBounds()
{
	return getSlav().getGlobalBounds();
}

Sprite Slav::getSlav()
{
	return slav;
}

void Slav::move()
{
	const float DISTANCE = 5.0;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		slav.move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels
		slav.move(DISTANCE, 0);
	}
}

void Slav::checkBounds(MooCows &cows)
{
	list<MooCow*>::iterator iterMooCow = cows.getMooCows().begin();
	list<MooCow*>::iterator cowEnd = cows.getMooCows().end();
	FloatRect cowBounds, slavBounds;

	if (!cows.getMooCows().empty())
	{
		MooCow* cow = *iterMooCow;
		for (iterMooCow; iterMooCow != cowEnd; )
		{
			slavBounds = getGlobalBounds();
			cowBounds = cow->getGlobalBounds();
			if (cowBounds.intersects(slavBounds))
			{
				iterMooCow = cows.getMooCows().erase(iterMooCow);
				lives--;
			}
			else
			{
				iterMooCow++;
			}
		}
	}
}