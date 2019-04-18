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
	UI gameUI;
	Sprite background;
	Slav player;
	Bottles playerWeapon;
	Boris boss;
	Texture enemyTexture,
		deepFriedTexture;
	MooCows enemyWeapon;
	int bossFrames, score;
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