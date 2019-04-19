#pragma once
#include <iostream>
#include <list>
#include "Bottle.h"
#include "Bottles.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

/*
Name: Bottles
Purpose: default constructor
Parameters: nothing
Returns: N/A
*/
Bottles::Bottles(){}

/*
Name: Bottles
Purpose: initializes list of bottles
Parameters: bottle texture
Returns: N/A
*/
Bottles::Bottles(Texture bottleTexture) {
	this->bottleTexture = bottleTexture;
}

/*
Name: get bottles
Purpose: gets list of bottles
Parameters: nothing
Returns: bottle list
*/
list<Bottle>& Bottles::getBottles() {
	return bottles;
}

/*
Name: add bottles
Purpose: adds an instance to the list
Parameters: position
Returns: nothing
*/
void Bottles::addBottle(Vector2f pos) {
	Sprite weapon;
	weapon.setTexture(bottleTexture);
	weapon.setPosition(pos);
	bottles.push_back(Bottle(weapon));
}

/*
Name: update position
Purpose: move bottles
Parameters: nothing
Returns: nothing
*/
void Bottles::updatePos() {
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

/*
Name: draw bottles
Purpose: renders bottles on screen
Parameters: window
Returns: nothing
*/
void Bottles::drawBottles(RenderWindow &win) {
	list<Bottle>::iterator iter;

	for (iter = bottles.begin(); iter != bottles.end(); iter++) {
		win.draw(iter->getBottle());
	}
}