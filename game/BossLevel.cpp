#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "BossLevel.h"

BossLevel::BossLevel(Texture &enemyTexture, int enemyFrames)
{
	this->enemyTexture = enemyTexture;
	Boris boss(enemyTexture);
	this->boss = boss;
	boss.setFrames(60);
	this->bossFrames = enemyFrames;
}

void BossLevel::renderLevel(RenderWindow &win, Sprite background)
{
	win.draw(background);
	gameUI.drawBossText(win, boss);
	win.draw(player.getSlav());
	playerWeapon.drawBottles(win);
	boss.drawBoris(win);
	enemyWeapon.drawMooCows(win);
}

void BossLevel::setBackground(Sprite background)
{
	this->background = background;
}

Slav BossLevel::getPlayer()
{
	return player;
}

void BossLevel::setPlayer(Slav s)
{
	player = s;
}

Bottles BossLevel::getPlayerWeapon()
{
	return playerWeapon;
}

void BossLevel::setPlayerWeapon(Bottles b)
{
	playerWeapon = b;
}

Boris BossLevel::getBoss()
{
	return boss;
}

MooCows BossLevel::getEnemyWeapon()
{
	return enemyWeapon;
}

void BossLevel::setEnemyWeapon(MooCows m)
{
	enemyWeapon = m;
}

int BossLevel::getEnemyFrames()
{
	return bossFrames;
}

bool BossLevel::playLevel(RenderWindow &win, bool canFire, int frames)
{
	// check all the window's events that were triggered since the last iteration of the loop
	// For now, we just need this so we can click on the window and close it
	Event event;
	bool levelComplete = false;
	

	while (win.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == Event::Closed)
			win.close();
		else if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Space && canFire)
			{
				// handle space bar
				Vector2f pos = player.getSlav().getPosition();
				playerWeapon.addBottle(pos);
				canFire = false;
			}

		}
	}

	//===========================================================
	// Everything from here to the end of the loop is where you put your
	// code to produce ONE frame of the animation. The next iteration of the loop will
	// render the next frame, and so on. All this happens ~ 60 times/second.
	//===========================================================

	// draw background first, so everything that's drawn later 
	// will appear on top of background
	int choice = rand() % 2 + 1;
	player.move();
	boss.updatePos();
	enemyWeapon = boss.throwMooCows(frames);
	playerWeapon.updatePos();
	boss.checkBounds(playerWeapon);
	player.checkBounds(enemyWeapon);

	// draw the ship on top of background 
	// (the ship from previous frame was erased when we drew background)
	renderLevel(win, background);
	// end the current frame; this makes everything that we have 
	// already "drawn" actually show up on the screen
	win.display();

	if (boss.getHealth() == 0)
	{
		levelComplete = true;
	}
	return levelComplete;
}