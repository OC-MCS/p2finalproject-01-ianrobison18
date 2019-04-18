#pragma once
#include <iostream>
#include <list>
#include "MooCow.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class MooCows
{
private:
	list<MooCow> cows;
	Texture cowTexture;
public:
	MooCows();
	MooCows(Texture enemyWeapon);
	list<MooCow> &getMooCows();
	void setTexture(Texture weapon);
	void addMooCow(Vector2f pos);
	void updatePos();
	void drawMooCows(RenderWindow &win);
};
