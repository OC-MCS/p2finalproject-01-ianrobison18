#pragma once
#include <iostream>
#include <list>
#include "WesternSpy.h"
#include "MooCows.h"
#include "Bottles.h"
#include "Slav.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class WesternSpies
{
private:
	list<WesternSpy> spies;
	int numSpies,
		framesTilFire;
	float movementSpeed;
public:
	WesternSpies();
	WesternSpies(Texture &spyTexture);
	list<WesternSpy> &getSpies();
	int getNumSpies();
	void setFrames(int frames);
	void setMovement(float movement);
	void updatePos(float speed, Slav &player);
	void drawWesternSpies(RenderWindow &win);
	void throwMooCows(int frames, MooCows &mutuallyAssuredDeath);
	bool checkBounds(Bottles &weapons);
};