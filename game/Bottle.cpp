#include <iostream>
#include "Bottle.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

Bottle::Bottle()
{

}

Bottle::Bottle(Sprite &bottle)
{
	this->bottle = bottle;
}

void Bottle::updatePosition()
{
	bottle.move(0, -20);
}

Sprite Bottle::getBottle()
{
	return bottle;
}

FloatRect Bottle::getGlobalBounds()
{
	return getBottle().getGlobalBounds();
}

void Bottle::setBottle(Sprite &bottle)
{
	this->bottle = bottle;
}

bool Bottle::operator==(Bottle compare)
{
	bool isEqual;
	if (bottle.getPosition() == compare.getBottle().getPosition())
	{
		isEqual = true;
	}
	else
	{
		isEqual = false;
	}

	return isEqual;
}