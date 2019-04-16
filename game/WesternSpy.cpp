#include <iostream>
#include "WesternSpy.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

WesternSpy::WesternSpy()
{

}

WesternSpy::WesternSpy(Sprite &spy)
{
	this->spy = spy;
}

void WesternSpy::updatePosition(float speed)
{
	spy.move(0, speed);
}

void WesternSpy::setSpeed(float speed)
{
	
}

Sprite WesternSpy::getSpy()
{
	return spy;
}


FloatRect WesternSpy::getGlobalBounds()
{
	return getSpy().getGlobalBounds();
}

void WesternSpy::setSpy(Sprite &spy)
{
	this->spy = spy;
}

bool WesternSpy::operator==(WesternSpy compare)
{
	bool isEqual;
	if (spy.getPosition() == compare.getSpy().getPosition())
	{
		isEqual = true;
	}
	else
	{
		isEqual = false;
	}

	return isEqual;
}
