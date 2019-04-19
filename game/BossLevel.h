#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Slav.h"
#include "Boris.h"
#include "Bottles.h"
#include "MooCows.h"
#include "UI.h"

class BossLevel
{
private:
	UI gameUI; // level ui
	Sprite background; // background
	Slav player; // player
	Bottles playerWeapon; // player's weapon
	Boris boss; // the slav king himself
	Texture enemyTexture, // boss texture
		deepFriedTexture; // his second texture
	MooCows enemyWeapon; // the boss's weapon
	int bossFrames, // the frames until he fires
		score; // current score
public:
	BossLevel(Texture &bossTexture, Texture &secondTexture, int bossFrames);
	void restartLevel(Texture &bossTexture, Texture &secondTexture);
	void renderLevel(RenderWindow &win, Sprite backGround);
	void setBackground(Sprite background);
	void setScore(int score);
	int getScore();
	void setUI(UI ui);
	Slav getPlayer();
	void setPlayer(Slav s);
	Bottles getPlayerWeapon();
	void setPlayerWeapon(Bottles b);
	Boris getBoss();
	MooCows getEnemyWeapon();
	void setEnemyWeapon(MooCows m);
	int getEnemyFrames();

	bool playLevel(RenderWindow &win, bool canFire, int frames, 
		bool &paused, bool &onMenu, bool &levelStart, bool &fail);
};