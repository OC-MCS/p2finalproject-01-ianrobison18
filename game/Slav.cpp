#include <iostream>
#include <list>
#include "Slav.h"
#include "MooCow.h"
#include "MooCows.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FARTHEST_LEFT = 0;
const int FARTHEST_RIGHT = WINDOW_WIDTH - 64;

/*
Name: Slav
Purpose: default constructor
Parameters: nothing 
Returns: N/A
*/
Slav::Slav() {

}

/*
Name: Slav
Purpose: initialize a slav
Parameters: Slav  sprite
Returns: N/A
*/
Slav::Slav(Sprite &slav) {
	this->slav = slav;
	lives = 5;
}

/*
Name: lose lives
Purpose: to decrement the life counter
Parameters: nothing
Returns: nothing
*/
void Slav::loseLives() {
	lives--;
}

/*
Name: set lives
Purpose: to set the slav's lives
Parameters: lives
Returns: nothing
*/
void Slav::setLives(int lives) {
	this->lives = lives;
}

/*
Name: get lives
Purpose: to return the lives 
Parameters: nothing
Returns: thel ives
*/
int Slav::getLives() {
	return lives;
}

/*
Name: get global bounds
Purpose: to get the bounds of the slav
Parameters: nothing
Returns: the bounds
*/
FloatRect Slav::getGlobalBounds() {
	return getSlav().getGlobalBounds();
}

/*
Name: get slav
Purpose: to get the sprite
Parameters: nothing
Returns: the slav sprite
*/
Sprite Slav::getSlav() {
	return slav;
}

/*
Name: move
Purpose: to move the slav
Parameters: nothing
Returns: nothing
*/
void Slav::move() {
	const float DISTANCE = 5.0;

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		slav.move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		// right arrow is pressed: move our ship right 5 pixels
		slav.move(DISTANCE, 0);
	}

	Vector2f shipPos = slav.getPosition();
	if (shipPos.x <= FARTHEST_LEFT) {
		slav.setPosition(FARTHEST_LEFT, shipPos.y);
	}
	else if (shipPos.x >= FARTHEST_RIGHT) {
		slav.setPosition(FARTHEST_RIGHT, shipPos.y);
	}
}

/*
Name: check bounds
Purpose: to check if he is hit
Parameters: moocows
Returns: nothing
*/
void Slav::checkBounds(MooCows &cows) {
	list<MooCow>::iterator iterMooCow = cows.getMooCows().begin();
	list<MooCow>::iterator cowEnd = cows.getMooCows().end();
	FloatRect cowBounds, slavBounds;

	if (!cows.getMooCows().empty()) {
		for (iterMooCow; iterMooCow != cowEnd; ) {
			slavBounds = getGlobalBounds();
			cowBounds = iterMooCow->getGlobalBounds();
			if (cowBounds.intersects(slavBounds)) {
				iterMooCow = cows.getMooCows().erase(iterMooCow);
				lives--;
			}
			else {
				iterMooCow++;
			}
		}
	}
}