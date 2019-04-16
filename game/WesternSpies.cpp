#pragma once
#include <iostream>
#include <list>
#include "WesternSpies.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

WesternSpies::WesternSpies()
{

}

WesternSpies::WesternSpies(Texture &spyTexture)
{
	Sprite newSpy;
	newSpy.setPosition(150, 50);
	newSpy.setTexture(spyTexture);
	WesternSpy spy(newSpy);
	WesternSpy *spyPtr = &spy;
	Vector2f pos = spyPtr->getSpy().getPosition();
	Sprite tempSpy = spyPtr->getSpy();
	numSpies = 10;

	for (int i = 1; i <= 2; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			spyPtr = new WesternSpy(tempSpy);
			spies.push_back(spyPtr);
			pos.x += 75;
			tempSpy = spyPtr->getSpy();
			tempSpy.setPosition(pos);
			spyPtr->setSpy(tempSpy);
		}
		pos.y += 75;
		pos.x = 150;
	}
}

list<WesternSpy*> WesternSpies::getSpies()
{
	return spies;
}

void WesternSpies::setFrames(int frames)
{
	framesTilFire = frames;
}

void WesternSpies::setMovement(float movement)
{
	movementSpeed = movement;
}

void WesternSpies::updatePos(float speed)
{
	list<WesternSpy*>::iterator iter;

	for (iter = spies.begin(); iter != spies.end(); )
	{
		(*iter)->setSpeed(speed);
		(*iter)->updatePosition(speed);
		Vector2f pos = (*iter)->getSpy().getPosition();
		if (pos.y <= -40)
		{
		}
		else
			iter++;
	}
}

int WesternSpies::getNumSpies()
{
	return numSpies;
}

void WesternSpies::drawWesternSpies(RenderWindow &win)
{
	list<WesternSpy*>::iterator iter;
	list<MooCow*>::iterator cowIter;

	for (iter = spies.begin(); iter != spies.end(); iter++)
	{
		win.draw((*iter)->getSpy());
	}
	mutuallyAssuredDeath.drawMooCows(win);
}

MooCows WesternSpies::throwMooCows(int frames)
{
	if (frames == 0)
	{
		int randomSpy = rand() % numSpies + 1;
		list<WesternSpy*>::iterator iter = spies.begin();
		
		for (int i = 1; i < randomSpy; i++)
		{
			iter++;
		}

		
		mutuallyAssuredDeath.addMooCow((*iter)->getSpy().getPosition());
	}
	if (!mutuallyAssuredDeath.getMooCows().empty())
	{
		mutuallyAssuredDeath.updatePos();
	}

	return mutuallyAssuredDeath;
}

void WesternSpies::checkBounds(Bottles &bottles)
{
	list<Bottle*>::iterator iterBottle = bottles.getBottles().begin();
	list<Bottle*>::iterator bottleEnd = bottles.getBottles().end();
	list<WesternSpy*>::iterator iterSpy = spies.begin();
	list<WesternSpy*>::iterator spyEnd = spies.end();
	FloatRect bottleBounds, enemyBounds;

	if (!bottles.getBottles().empty())
	{
		for (iterBottle; iterBottle != bottleEnd; )
		{
			for (iterSpy; iterSpy != spyEnd; )
			{
				bottleBounds = (*iterBottle)->getGlobalBounds();
				enemyBounds = (*iterSpy)->getGlobalBounds();
				if (bottleBounds.intersects(enemyBounds))
				{
					iterBottle = bottles.getBottles().erase(iterBottle);
					iterSpy = spies.erase(iterSpy);
				}
				else
				{
					iterBottle++;
					iterSpy++;
				}
			}
		}
	}
}