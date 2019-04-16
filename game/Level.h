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
	int level, enemyFrames;
	float speed;
public:
	Level(Texture &enemyTexture, int enemyFrames, float speed);
	void renderLevel(RenderWindow &win, Sprite backGround);
	void setBackground(Sprite background);
	Slav getPlayer();
	void setPlayer(Slav s);
	Bottles getPlayerWeapon();
	void setPlayerWeapon(Bottles b);
	WesternSpies getEnemies();
	MooCows getEnemyWeapon();
	void setEnemyWeapon(MooCows m);
	int getEnemyFrames();

	bool playLevel(RenderWindow &win, bool canFire, int frames);
};