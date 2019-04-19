#include <iostream>
#include "MooCows.h"
#include "Bottles.h"
#include "Boris.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FARTHEST_LEFT =-7;
const int FARTHEST_RIGHT = WINDOW_WIDTH - 120;

/*
Name: Boris
Purpose: Default constructor
Parameters: Nothing
Returns: N/A
*/
Boris::Boris() {

}

/*
Name: Boris
Purpose: Initialize an instance of boris
Parameters: a texture for the boss
Returns: N/A
*/
Boris::Boris(Texture &bossTexture) {
	boris.setPosition(400, 100);
	boris.setTexture(bossTexture);
	health = 25;
	direction = false;
}

/*
Name: Get Global Bounds
Purpose: returns the global bounds of the boss
Parameters: nothing
Returns FloatRect bounds
*/
FloatRect Boris::getGlobalBounds() {
	return boris.getGlobalBounds();
}

/*
Name: get Sprite
Purpose: returns the sprite of the boss
Parameters: nothing
Returns: the sprite
*/
Sprite Boris::getSprite() {
	return boris;
}

/*
Name: get Health
Purpose: get the boss health
Parameters: nothing
Returns: health
*/
int Boris::getHealth() {
	return health;
}

/*
Name: set Deep Fried
Purpose: sets the second texture of the boss
Parameters: a new texture
Returns: nothing
*/
void Boris::setDeepFried(Texture &deepFried) {
	boris.setTexture(deepFried);
}

/*
Name: set frames
Purpose: set the frames that it takes for the boss to fire again
Parameters: new frame amount
Returns: nothing
*/
void Boris::setFrames(int frames) {
	framesTilFire = frames;
}

/*
Name: set Movement
Purpose: set the speed of the boss
Parameters: movement amount
Returns: nothing
*/
void Boris::setMovement(float movement) {
	speed = movement;
}

/*
Name: update position
Purpose: moves the boss
Parameters: nothing
Returns: nothing
*/
void Boris::updatePos() {
	
	if (direction)
		boris.move(5, 0);
	else
		boris.move(-5, 0);

	Vector2f borisPos = boris.getPosition();
	if (borisPos.x <= FARTHEST_LEFT) {
		direction = true;
	}
	else if (borisPos.x >= FARTHEST_RIGHT) {
		direction = false;
	}
}

/*
Name: draw Boris
Purpose: draws the boss
Parameters: Render window
Returns: nothing
*/
void Boris::drawBoris(RenderWindow &win) {
	win.draw(boris);
}

/*
Name: throw Moocows
Purpose: adds a moo cow to the list
Parameters: frames until fire and moo cows
Returns: nothing
*/
void Boris::throwMooCows(int frames, MooCows &trueDeath) {
	if (frames == 0) {
 		trueDeath.addMooCow(boris.getPosition());
	}
	if (!trueDeath.getMooCows().empty()) {
		trueDeath.updatePos();
	}
}

/*
Name: check bounds
Purpose: checks if the boss is hit and decrements health if hit
Parameters: list of bottles
Returns: a bool if hit
*/
bool Boris::checkBounds(Bottles &bottles) {
	list<Bottle>::iterator iterBottle = bottles.getBottles().begin();
	list<Bottle>::iterator bottleEnd = bottles.getBottles().end();
	FloatRect bottleBounds, enemyBounds;
	bool hit = false;

	// Only activates if the list of bottles isn't empty
	if (!bottles.getBottles().empty()) {
		for (iterBottle; iterBottle != bottleEnd && !hit; ) {
			enemyBounds = getGlobalBounds();
			bottleBounds = iterBottle->getGlobalBounds();
			// If a bottle hits Boris, erase bottle, decrement health
			if (bottleBounds.intersects(enemyBounds)) {
				iterBottle = bottles.getBottles().erase(iterBottle);
				health--;
				hit = true;
			}
			else { // else, go to next bottle
				iterBottle++;
			}
		}
	}
	return hit;
}