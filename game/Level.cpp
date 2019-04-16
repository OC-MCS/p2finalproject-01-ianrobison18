#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Level.h"

Level::Level(Texture &enemyTexture,  int enemyFrames, float speed)
{
	this->enemyTexture = enemyTexture;
	WesternSpies enemy(enemyTexture);
	enemies = enemy;
	enemies.setFrames(60);
	this->speed = speed;
	this->enemyFrames = enemyFrames;
}

void Level::renderLevel(RenderWindow &win, Sprite background)
{
	win.draw(background);
	win.draw(player.getSlav());
	playerWeapon.drawBottles(win);
	enemies.drawWesternSpies(win);
	enemyWeapon.drawMooCows(win);
}

void Level::setBackground(Sprite background)
{
	this->background = background;
}

Slav Level::getPlayer()
{
	return player;
}

void Level::setPlayer(Slav s)
{
	player = s;
}

Bottles Level::getPlayerWeapon()
{
	return playerWeapon;
}

void Level::setPlayerWeapon(Bottles b)
{
	playerWeapon = b;
}

WesternSpies Level::getEnemies()
{
	return enemies;
}

MooCows Level::getEnemyWeapon()
{
	return enemyWeapon;
}

void Level::setEnemyWeapon(MooCows m)
{
	enemyWeapon = m;
}

int Level::getEnemyFrames()
{
	return enemyFrames;
}

bool Level::playLevel(RenderWindow &win, bool canFire, int frames)
{
	// check all the window's events that were triggered since the last iteration of the loop
	// For now, we just need this so we can click on the window and close it
	Event event;
	bool levelComplete = false;
	bool paused;

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
			else if (event.key.code == Keyboard::Escape )
			{
				paused = true;
				while (paused)
				{
					gameUI.drawPauseMenu(win);
				}
				paused = false;
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

	player.move();
	enemies.updatePos(speed);
	enemyWeapon = enemies.throwMooCows(frames);
	playerWeapon.updatePos();
	enemies.checkBounds(playerWeapon);
	player.checkBounds(enemyWeapon);

	// draw the ship on top of background 
	// (the ship from previous frame was erased when we drew background)
	renderLevel(win, background);
	
	// end the current frame; this makes everything that we have 
	// already "drawn" actually show up on the screen
	win.display();

	if (enemies.getNumSpies() == 0)
	{
		levelComplete = true;
	}
	return levelComplete;
}