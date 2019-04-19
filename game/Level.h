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
	UI gameUI; // ui for level
	Sprite background; // level background
	Slav player; // player
	Bottles playerWeapon; // player's weapon
	WesternSpies enemies; // level enemies
	Texture enemyTexture; // current enemy texture
	MooCows enemyWeapon; // enemy weapon
	int level, // current level
		enemyFrames, // frames until enemy fires
		score; // current score
	float speed; // speed of enemies
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