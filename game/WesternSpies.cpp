#pragma once
#include <iostream>
#include <list>
#include "WesternSpies.h"
#include "Slav.h"
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
	Vector2f pos = spy.getSpy().getPosition();
	Sprite tempSpy = spy.getSpy();
	numSpies = 10;

	for (int i = 1; i <= 2; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			spies.push_back(spy);
			pos.x += 75;
			tempSpy = spy.getSpy();
			tempSpy.setPosition(pos);
			spy.setSpy(tempSpy);
		}
		pos.y += 75;
		pos.x = 150;
	}
}

list<WesternSpy> &WesternSpies::getSpies()
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

void WesternSpies::updatePos(float speed, Slav &player)
{
	list<WesternSpy>::iterator iter;

	for (iter = spies.begin(); iter != spies.end(); )
	{
		iter->setSpeed(speed);
		iter->updatePosition(speed);
		Vector2f pos = iter->getSpy().getPosition();
		if (pos.y <= -40)
		{
			player.loseLives();
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
	list<WesternSpy>::iterator iter;

	for (iter = spies.begin(); iter != spies.end(); iter++)
	{
		win.draw(iter->getSpy());
	}
}

void WesternSpies::throwMooCows(int frames, MooCows &mutuallyAssuredDeath)
{
	if (frames == 0)
	{
		int randomSpy = rand() % numSpies + 1;
		list<WesternSpy>::iterator iter = spies.begin();
		
		for (int i = 1; i < randomSpy; i++)
		{
			iter++;
		}

		
		mutuallyAssuredDeath.addMooCow(iter->getSpy().getPosition());
	}
	if (!mutuallyAssuredDeath.getMooCows().empty())
	{
		mutuallyAssuredDeath.updatePos();
	}

}

bool WesternSpies::checkBounds(Bottles &bottles)
{
	list<Bottle>::iterator iterBottle = bottles.getBottles().begin();
	list<Bottle>::iterator bottleEnd = bottles.getBottles().end();
	list<WesternSpy>::iterator iterSpy = spies.begin();
	list<WesternSpy>::iterator spyEnd = spies.end();
	FloatRect bottleBounds, enemyBounds;
	bool hit = false;

	if (!bottles.getBottles().empty())
	{
		for (iterBottle; iterBottle != bottleEnd && !hit; )
		{
			for (iterSpy; iterSpy != spyEnd && !hit; )
			{
				bottleBounds = iterBottle->getGlobalBounds();
				enemyBounds = iterSpy->getGlobalBounds();
 				if (bottleBounds.intersects(enemyBounds))
				{
					iterBottle = bottles.getBottles().erase(iterBottle);
					iterSpy = spies.erase(iterSpy);
					numSpies--;
					hit = true;
				}
				else
				{
					iterSpy++;
				}
			}
			if (!hit) 
				iterBottle++;
		}
	}
	return hit;
}