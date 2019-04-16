#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bottle
{
private:
	Sprite bottle;
public:
	Bottle();
	Bottle(Sprite &bottle);
	void updatePosition();
	Sprite *getBottle();
	FloatRect getGlobalBounds();
	void setBottle(Sprite &bottle);
	bool operator==(Bottle compare);
};