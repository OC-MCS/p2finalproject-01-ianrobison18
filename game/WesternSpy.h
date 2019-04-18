#pragma once
#include <iostream>
#include "MooCow.h"
#include "MooCows.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class WesternSpy
{
private:
	Sprite spy;
	int health;
public:
	WesternSpy();
	WesternSpy(Sprite &spy);
	void updatePosition(float speed);
	void setSpeed(float speed);
	Sprite getSpy();
	FloatRect getGlobalBounds();
	void setSpy(Sprite &spy);
	bool operator==(WesternSpy compare);
};