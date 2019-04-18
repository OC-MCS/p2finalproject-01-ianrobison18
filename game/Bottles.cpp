#pragma once
#include <iostream>
#include <list>
#include "Bottle.h"
#include "Bottles.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


Bottles::Bottles()
{

}

Bottles::Bottles(Texture bottleTexture)
{
	this->bottleTexture = bottleTexture;
}

list<Bottle>& Bottles::getBottles()
{
	return bottles;
}

void Bottles::addBottle(Vector2f pos)
{
	Sprite weapon;
	weapon.setTexture(bottleTexture);
	weapon.setPosition(pos);
	bottles.push_back(Bottle(weapon));
}

void Bottles::updatePos()
{
	list<Bottle>::iterator iter;

	for (iter = bottles.begin(); iter != bottles.end(); )
	{
 		iter->updatePosition();
		Vector2f pos = iter->getBottle().getPosition();
		if (pos.y <= -40)
		{
			iter = bottles.erase(iter);
		}
		else
			iter++;
	}
}

void Bottles::drawBottles(RenderWindow &win)
{
	list<Bottle>::iterator iter;

	for (iter = bottles.begin(); iter != bottles.end(); iter++)
	{
		win.draw(iter->getBottle());
	}
}

