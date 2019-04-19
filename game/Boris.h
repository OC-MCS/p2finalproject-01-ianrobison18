#pragma once
#include <iostream>
#include "MooCows.h"
#include "Bottles.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Boris
{
private:
	Sprite boris; // boss sprite
	MooCows trueDeath; // him weapon
	int framesTilFire, // frames until he fires
		health; // his health
	float speed; // his speed
	bool direction; // his current direction
	// false = left, true = right
public:
	Boris();
	Boris(Texture &bossTexture);
	Sprite getSprite();
	FloatRect getGlobalBounds();
	int getHealth();
	void setDeepFried(Texture &deepFried);
	void setFrames(int frames);
	void setMovement(float movement);
	void updatePos();
	void drawBoris(RenderWindow &win);
	void throwMooCows(int frames, MooCows &trueDeath);
	bool checkBounds(Bottles &weapons);
};