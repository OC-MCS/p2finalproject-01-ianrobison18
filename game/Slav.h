#pragma once
#include <iostream>
#include "MooCows.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Slav
{
private:
	Sprite slav;
	int lives;
public:
	Slav();
	Slav(Sprite &slav);
	FloatRect getGlobalBounds();
	void setLives(int lives);
	int getLives();
	void loseLives();
	Sprite getSlav();
	void move();
	void checkBounds(MooCows &cows);
};