#pragma once
#include <iostream>
#include <list>
#include "WesternSpy.h"
#include "MooCows.h"
#include "Bottles.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class WesternSpies
{
private:
	list<WesternSpy*> spies;
	MooCows mutuallyAssuredDeath;
	int numSpies,
		framesTilFire;
	float movementSpeed;
public:
	WesternSpies();
	WesternSpies(Texture &spyTexture);
	list<WesternSpy*> getSpies();
	int getNumSpies();
	void setFrames(int frames);
	void setMovement(float movement);
	void updatePos(float speed);
	void drawWesternSpies(RenderWindow &win);
	MooCows throwMooCows(int frames);
	void checkBounds(Bottles &weapons);
};