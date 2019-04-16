//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
#include <list>
#include "Slav.h"
#include "Bottles.h"
#include "WesternSpies.h"
#include "MooCows.h"
#include "Boris.h"
#include "Level.h"
#include "BossLevel.h"
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;


//============================================================
// Ian Robison
// Programming II
// Space Shooter Game
//============================================================

bool checkFrames(int &frames, bool canFire);
void checkEnemyFrames(Level currentLevel, int &frames);
int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	
	Texture starsTexture;
	if (!starsTexture.loadFromFile("StPetersburg.png"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture slavTexture;
	if (!slavTexture.loadFromFile("Slav.png"))
	{
		cout << "Unable to load slav texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bottleTexture;
	if (!bottleTexture.loadFromFile("Bottle.png"))
	{
		cout << "Unable to load bottle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture westernSpyTexture;
	if (!westernSpyTexture.loadFromFile("enemy.png"))
	{
		cout << "Unable to load spy texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture enemySlavTexture;
	if (!enemySlavTexture.loadFromFile("enemySlav.png"))
	{
		cout << "Unable to load enemy Slav texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture borisTexture;
	if (!borisTexture.loadFromFile("SlavKing.png"))
	{
		cout << "Unable to load Slav King texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Level levelOne(westernSpyTexture, 60, 0.3);
	Level levelTwo(enemySlavTexture, 40, 0.45);
	BossLevel slavKingFight(borisTexture, 15);
	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite background;
	background.setTexture(starsTexture);
	levelOne.setBackground(background);
	levelTwo.setBackground(background);
	slavKingFight.setBackground(background);

	// Slav sprite data
	Sprite slavic;
	slavic.setTexture(slavTexture);
	float slavX = 300;
	float slavY = 500;
	slavic.setPosition(slavX, slavY);
	Slav slav(slavic);
	levelOne.setPlayer(slav);
	levelTwo.setPlayer(slav);
	slavKingFight.setPlayer(slav);

	// Bottle data
	Bottles bottles(bottleTexture);
	levelOne.setPlayerWeapon(bottles);
	levelTwo.setPlayerWeapon(bottles);
	slavKingFight.setPlayerWeapon(bottles);

	Music gameMusic;
	if (!gameMusic.openFromFile("gameMusic.ogg"))
	{
		cout << "Unable to load in game music!" << endl;
		exit(EXIT_FAILURE);
	}

	SoundBuffer cheekiBuffer;
	if (!cheekiBuffer.loadFromFile("cheekiBreeki.ogg"))
	{
		cout << "unable to load cheeki breeki!" << endl;
		exit(EXIT_FAILURE);
	}
	Sound cheekiBreeki;
	cheekiBreeki.setBuffer(cheekiBuffer);
	cheekiBreeki.setVolume(100.f);
	bool playCheekiBreeki = true;
	gameMusic.setVolume(40.f);
	gameMusic.play();
	gameMusic.setLoop(true);

	int frames = 0;
	int enemyFrames = 0;
	int level = 1;
	bool canFire = true,
		levelComplete = false;
	
	while (window.isOpen())
	{
		canFire = checkFrames(frames, canFire);
		checkEnemyFrames(levelOne, enemyFrames);
		if (level == 1)
		{
			levelComplete = levelOne.playLevel(window, canFire, enemyFrames);
			if (levelComplete)
			{
				level++;
				levelComplete = false;
			}
		}
		else if (level == 2)
		{
			levelComplete = levelTwo.playLevel(window, canFire, enemyFrames);
			if (levelComplete)
			{
				level++;
				levelComplete = false;
			}
		}
		else if (level == 3)
		{
			while (playCheekiBreeki)
			{
				cheekiBreeki.play();
				playCheekiBreeki = false;
			}
			levelComplete = slavKingFight.playLevel(window, canFire, enemyFrames);
			if (levelComplete)
			{
				level++;
				levelComplete = false;
			}
		}
		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

 	} // end body of animation loop

	return 0;
}

bool checkFrames(int &frames, bool canFire)
{
	frames++;
	if (frames == 60)
	{
		frames = 0;
	}
	if (frames % 15 == 0)
	{
		canFire = true;
	}

	return canFire;
}

void checkEnemyFrames(Level currentLevel, int &frames)
{
	frames++;
	if (frames == currentLevel.getEnemyFrames())
	{
		frames = 0;
	}
}