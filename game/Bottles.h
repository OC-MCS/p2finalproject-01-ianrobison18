#pragma once
#include <iostream>
#include <list>
#include "Bottle.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bottles
{
private:
	list<Bottle*> bottles;
	Texture bottleTexture;
public:
	Bottles();
	Bottles(Texture bottleTexture);
	list<Bottle*> getBottles();
	void addBottle(Vector2f pos);
	void updatePos();
	void drawBottles(RenderWindow &win);
};