#include <iostream>
#include "MooCow.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

MooCow::MooCow()
{
	
}

MooCow::MooCow(Sprite &cow)
{
	this->cow = cow;
}

void MooCow::updatePosition()
{
	cow.move(0, 5);
}

FloatRect MooCow::getGlobalBounds()
{
	return getMooCow().getGlobalBounds();
}

Sprite MooCow::getMooCow()
{
	return cow;
}

void MooCow::setMooCow(Sprite &cow)
{
	this->cow = cow;
}

bool MooCow::operator==(MooCow compare)
{
	bool isEqual;
	if (cow.getPosition() == compare.getMooCow().getPosition())
	{
		isEqual = true;
	}
	else
	{
		isEqual = false;
	}

	return isEqual;
}