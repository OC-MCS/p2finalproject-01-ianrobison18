#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Slav.h"
#include "WesternSpies.h"
#include "Bottles.h"
#include "MooCows.h"
#include "UI.h"

class Level
{
private:
	UI gameUI;
	Sprite background;
	Slav player;
	Bottles playerWeapon;
	WesternSpies enemies;
	Texture enemyTexture;
	MooCows enemyWeapon;
	int level, enemyFrames, score;
	float speed;
public:
	Level();
	Level(Texture &enemyTexture, int enemyFrames, float speed);
	void restartLevel(Texture &enemyTexture);
	void renderLevel(RenderWindow &win, Sprite backGround);
	void setBackground(Sprite background);
	void setScore(int score);
	int getScore();
	void setUI(UI ui);
	Slav getPlayer();
	void setPlayer(Slav s);
	Bottles getPlayerWeapon();
	void setPlayerWeapon(Bottles b);
	WesternSpies getEnemies();
	MooCows getEnemyWeapon();
	void setEnemyWeapon(MooCows m);
	int getEnemyFrames();

	bool playLevel(RenderWindow &win, bool canFire, int frames, 
		bool &paused, bool &onMenu, bool &levelStart, bool &fail);
};