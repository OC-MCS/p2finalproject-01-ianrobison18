#include <iostream>
#include "Bottle.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

/*
Name: Bottle
Purpose: default constructor
Parameters: nothing 
Returns: N/A
*/
Bottle::Bottle() {}

/*
Name: Bottle
Purpose: initialize a bottle
Parameters: sprite cranberry
Returns: N/A
*/
Bottle::Bottle(Sprite &bottle) {
	this->bottle = bottle;
}

/*
Name: update position
Purpose: move bottle
Parameters: nothing
Returns: nothing
*/
void Bottle::updatePosition() {
	bottle.move(0, -20);
}

/*
Name: get Bottle
Purpose: get bottle
Parameters: nothing
Returns: Sprite cranberry
*/
Sprite Bottle::getBottle() {
	return bottle;
}

/*
Name: get global bounds
Purpose: get the bounds of the bottle
Parameters: nothing
Returns: bounds
*/
FloatRect Bottle::getGlobalBounds() {
	return getBottle().getGlobalBounds();
}

/*
Name: set Bottle
Purpose: set bottle
Parameters: Sprite cranberry
Returns: nothing
*/
void Bottle::setBottle(Sprite &bottle) {
	this->bottle = bottle;
}

/*
Name: == operator
Purpose: to compare two bottles to see which shall dominate
Parameters: other bottle of sprite cranberry
Returns: bool
*/
bool Bottle::operator==(Bottle compare) {
	bool isEqual;
	if (bottle.getPosition() == compare.getBottle().getPosition()) {
		isEqual = true;
	}
	else {
		isEqual = false;
	}
	return isEqual;
}