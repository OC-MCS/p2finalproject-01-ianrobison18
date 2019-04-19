#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class MooCow
{
private:
	Sprite cow; // cow sprite
public:
	MooCow();
	MooCow(Sprite &cow);
	void updatePosition();
	FloatRect getGlobalBounds();
	Sprite getMooCow();
	void setMooCow(Sprite &cow);
	bool operator==(MooCow compare);
};