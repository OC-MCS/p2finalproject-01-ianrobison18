#pragma once
#include <iostream>
#include <list>
#include "WesternSpies.h"
#include "Slav.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

/*
Name: WesternSpies
Purpose: default constructor
Parameters: nothing
Returns: N/A
*/
WesternSpies::WesternSpies() {

}

/*
Name: WesternSpies
Purpose: initialize list of spies and locations
Parameters: texture
Returns: N/A
*/
WesternSpies::WesternSpies(Texture &spyTexture) {
	Sprite newSpy;
	newSpy.setPosition(150, 50);
	newSpy.setTexture(spyTexture);
	WesternSpy spy(newSpy);
	Vector2f pos = spy.getSpy().getPosition();
	Sprite tempSpy = spy.getSpy();
	numSpies = 10;

	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 5; j++) {
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

/*
Name: get spies
Purpose: returns the list
Parameters: nothing
Returns: list of spies
*/
list<WesternSpy> &WesternSpies::getSpies() {
	return spies;
}

/*
Name: set frames
Purpose: set frames until they can fire
Parameters: frames
Returns: nothing
*/
void WesternSpies::setFrames(int frames) {
	framesTilFire = frames;
}



/*
Name: update position
Purpose: move the spies
Parameters: speed and the player
Returns: nothing
*/
void WesternSpies::updatePos(float speed, Slav &player) {
	list<WesternSpy>::iterator iter;

	for (iter = spies.begin(); iter != spies.end(); ) {
		iter->setSpeed(speed);
		iter->updatePosition(speed);
		Vector2f pos = iter->getSpy().getPosition();
		if (pos.y <= -40) {
			player.loseLives();
		}
		else
			iter++;
	}
}

/*
Name: get num spies
Purpose: returns current number of spies
Parameters: nothing
Returns: number of spies left
*/
int WesternSpies::getNumSpies() {
	return numSpies;
}

/*
Name: draw spies
Purpose: render them in the level
Parameters: window
Returns: nothing
*/
void WesternSpies::drawWesternSpies(RenderWindow &win) {
	list<WesternSpy>::iterator iter;

	for (iter = spies.begin(); iter != spies.end(); iter++) {
		win.draw(iter->getSpy());
	}
}

/*
Name: throw moocows
Purpose: add moocows to the list and move them
Parameters: frames and moocows
Returns: death to the player
*/
void WesternSpies::throwMooCows(int frames, MooCows &mutuallyAssuredDeath) {
	if (frames == 0) {
		int randomSpy = rand() % numSpies + 1;
		list<WesternSpy>::iterator iter = spies.begin();
		
		for (int i = 1; i < randomSpy; i++) {
			iter++;
		}

		
		mutuallyAssuredDeath.addMooCow(iter->getSpy().getPosition());
	}
	if (!mutuallyAssuredDeath.getMooCows().empty()) {
		mutuallyAssuredDeath.updatePos();
	}

}

/*
Name: check bounds
Purpose: check if they've been hit
Parameters: bottles
Returns: bool if hit
*/
bool WesternSpies::checkBounds(Bottles &bottles) {
	list<Bottle>::iterator iterBottle = bottles.getBottles().begin();
	list<Bottle>::iterator bottleEnd = bottles.getBottles().end();
	list<WesternSpy>::iterator iterSpy = spies.begin();
	list<WesternSpy>::iterator spyEnd = spies.end();
	FloatRect bottleBounds, enemyBounds;
	bool hit = false;

	if (!bottles.getBottles().empty()) {
		for (iterBottle; iterBottle != bottleEnd && !hit; ) {
			for (iterSpy; iterSpy != spyEnd && !hit; ) {
				bottleBounds = iterBottle->getGlobalBounds();
				enemyBounds = iterSpy->getGlobalBounds();
 				if (bottleBounds.intersects(enemyBounds)) {
					iterBottle = bottles.getBottles().erase(iterBottle);
					iterSpy = spies.erase(iterSpy);
					numSpies--;
					hit = true;
				}
				else {
					iterSpy++;
				}
			}
			if (!hit) 
				iterBottle++;
		}
	}
	return hit;
}