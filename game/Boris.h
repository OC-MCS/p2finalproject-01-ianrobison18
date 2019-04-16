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
	Sprite boris;
	MooCows trueDeath;
	int framesTilFire,
		health;
	float speed;
	bool direction;
public:
	Boris();
	Boris(Texture &bossTexture);
	Sprite getSprite();
	FloatRect getGlobalBounds();
	int getHealth();
	void setFrames(int frames);
	void setMovement(float movement);
	void updatePos();
	void drawBoris(RenderWindow &win);
	MooCows throwMooCows(int frames);
	void checkBounds(Bottles &weapons);
};