#include <iostream>
#include "WesternSpy.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

/*
Name: Western Spy
Purpose: default constructor
Parameters: nothing
Returns: N/A
*/
WesternSpy::WesternSpy() {

}

/*
Name: WesternSpy
Purpose: initializes an instance
Parameters: spy sprite
Returns: N/A
*/
WesternSpy::WesternSpy(Sprite &spy) {
	this->spy = spy;
}

/*
Name: update position
Purpose: move the spy
Parameters: speed
Returns: nothing
*/
void WesternSpy::updatePosition(float speed) {
	spy.move(0, speed);
}

/*
Name: set speed
Purpose: set movement speed
Parameters: speed
Returns: nothing
*/
void WesternSpy::setSpeed(float speed) {
	
}

/*
Name: get spy
Purpose: gets the sprite
Parameters: nothing
Returns: sprite
*/
Sprite WesternSpy::getSpy() {
	return spy;
}

/*
Name: get global bounds
Purpose: gets the bounds of the spy
Parameters: nothing
Returns: bounds
*/
FloatRect WesternSpy::getGlobalBounds() {
	return getSpy().getGlobalBounds();
}

/*
Name: set spy
Purpose: sets the sprite
Parameters: sprite
Returns: nothing
*/
void WesternSpy::setSpy(Sprite &spy) {
	this->spy = spy;
}

/*
Name: == operator
Purpose: compare two spies
Parameters: other spy
Returns: a bool
*/
bool WesternSpy::operator==(WesternSpy compare) {
	bool isEqual;
	if (spy.getPosition() == compare.getSpy().getPosition()) {
		isEqual = true;
	}
	else {
		isEqual = false;
	}

	return isEqual;
}