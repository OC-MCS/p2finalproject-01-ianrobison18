#pragma once
#include <iostream>
#include <list>
#include "MooCow.h"
#include "MooCows.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

/*
Name: MooCows
Purpose: initialize the moocows
Parameters: nothing
Returns: N/A
*/
MooCows::MooCows() {
	if (!cowTexture.loadFromFile("mooCow.png")) {
		cout << "Unable to load mooCow texture!" << endl;
		exit(EXIT_FAILURE);
	}
}

/*
Name: get moocows
Purpose: get mowcows
Parameters: nothing
Returns: MOOCOWS!!!!
*/
list<MooCow> &MooCows::getMooCows() {
	return cows;
}

/*
Name: set texture
Purpose: set the texture
Parameters: texture
Returns: nothing
*/
void MooCows::setTexture(Texture enemyTexture) {
	cowTexture = enemyTexture;
}

/*
Name: add moocow
Purpose: add to the list
Parameters: position
Returns: nothing
*/
void MooCows::addMooCow(Vector2f pos) {
	Sprite cow;
	cow.setPosition(pos);
	cow.setTexture(cowTexture);
	cows.push_back(MooCow(cow));
}

/*
Name: update position
Purpose: move moocows
Parameters: nothing
Returns nothing
*/
void MooCows::updatePos() {
	list<MooCow>::iterator iter;

	for (iter = cows.begin(); iter != cows.end(); ) {
		iter->updatePosition();
		Vector2f pos = iter->getMooCow().getPosition();
		if (pos.y >= 600) {
			iter = cows.erase(iter);
		}
		else
			iter++;
	}
}

/*
Name: draw moocows
Purpose: render the cows
Parameters: window
Returns: nothing
*/
void MooCows::drawMooCows(RenderWindow &win) {
	list<MooCow>::iterator iter;

	for (iter = cows.begin(); iter != cows.end(); iter++) {
		win.draw(iter->getMooCow());
	}
}
