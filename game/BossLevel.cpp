#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "BossLevel.h"

/*
Name: Boss Level
Purpose: Constructor for the boss level
Parameters: first boss texture, second boss texture, the frames until he fires
Returns: N/A
*/
BossLevel::BossLevel(Texture &enemyTexture, Texture &secondTexture, int enemyFrames) {
	this->enemyTexture = enemyTexture;
	Boris boss(enemyTexture);
	this->deepFriedTexture = secondTexture;
	this->boss = boss;
	boss.setFrames(60);
	this->bossFrames = enemyFrames;
	score = 0;
}

/*
Name: Restart Level
Purpose: restart the level
Parameters: the textures
Returns: nothing
*/
void BossLevel::restartLevel(Texture &bossTexture, Texture &secondTexture) {
	this->enemyTexture = enemyTexture;
	Boris boss(enemyTexture);
	this->deepFriedTexture = secondTexture;
	this->boss = boss;
	boss.setFrames(60);
}

/*
Name: Render Level
Purpose: render the level
Parameters: render window, the background
Returns: nothing
*/
void BossLevel::renderLevel(RenderWindow &win, Sprite background) {
	win.draw(background);
	gameUI.drawBossText(win, boss, player, score);
	win.draw(player.getSlav());
	playerWeapon.drawBottles(win);
	boss.drawBoris(win);
	enemyWeapon.drawMooCows(win);
}

/*
Name: set background
Purpose: sets the level background
Parameters: the background
Returns: nothing
*/
void BossLevel::setBackground(Sprite background) {
	this->background = background;
}

/*
Name: set score
Purpose: to set the level's score
Parameters: the score from the previous level
Returns: nothing
*/
void BossLevel::setScore(int score) {
	this->score = score;
}

/*
Name: get score
Purpose: gets the level score
Parameters: nothing
Returns: the score
*/
int BossLevel::getScore() {
	return score;
}

/*
Name: set ui
Purpose: sets the level for the ui
Parameters: the ui
Returns: nothing
*/
void BossLevel::setUI(UI ui) {
	this->gameUI = ui;
}

/*
Name: get player
Purpose: gets the player
Parameters: nothing
Returns: slav
*/
Slav BossLevel::getPlayer() {
	return player;
}

/*
Name: set player
Purpose: sets the sprite for the player
Parameters: slav
Returns: nothing
*/
void BossLevel::setPlayer(Slav s) {
	player = s;
}

/*
Name: get player weapon
Purpose: returns the bottles
Parameters: nothing
Returns: the bottles
*/
Bottles BossLevel::getPlayerWeapon() {
	return playerWeapon;
}

/*
Name: set player weapon
Purpose: sets the bottles
Parameters: bottles
Returns: nothing
*/
void BossLevel::setPlayerWeapon(Bottles b) {
	playerWeapon = b;
}

/*
Name: get boss
Purpose: get the level boss
Parameters: nothing
Returns: Boris
*/
Boris BossLevel::getBoss() {
	return boss;
}

/*
Name: get enemy weapon
Purpose: gets the moocows
Parameters: nothing
Returns moocows
*/
MooCows BossLevel::getEnemyWeapon() {
	return enemyWeapon;
}

/*
Name: set enemy weapon
Purpose: sets the moocows
Parameters: moocows
Returns: nothing
*/
void BossLevel::setEnemyWeapon(MooCows m) {
	enemyWeapon = m;
}

/*
Name: get enemy frames
Purpose: returns the frames for the enemy to fire
Parameters: nothing
Returns: the frames
*/
int BossLevel::getEnemyFrames() {
	return bossFrames;
}

/*
Name: Play level
Purpose: plays through the boss level
Parameters: render window, if player can fire, current frames on, if paused, if on menu, 
if level started, if player failed
Returns: if level is complete
*/
bool BossLevel::playLevel(RenderWindow &win, bool canFire, int frames, 
	bool &paused, bool &onMenu, bool &levelStart, bool &fail) {
	// check all the window's events that were triggered since the last iteration of the loop
	// For now, we just need this so we can click on the window and close it
	Event event;
	bool levelComplete = false,
		hit = false;
	
	while (win.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Space && canFire) {
				// handle space bar
				Vector2f pos = player.getSlav().getPosition();
				playerWeapon.addBottle(pos);
				canFire = false;
			}
			else if (event.key.code == Keyboard::Escape && !paused) {
				paused = true;
			}
			else if (event.key.code == Keyboard::Escape && paused) {
				paused = false;
			}
		}
		else if (event.type == Event::MouseMoved) {
			Vector2f mousePos = win.mapPixelToCoords(Mouse::getPosition(win));
			gameUI.pauseMenuMouse(mousePos); 
		}
		if (event.type == Event::MouseButtonReleased) {
			Vector2f mousePos = win.mapPixelToCoords(Mouse::getPosition(win));
			if (paused && levelStart)
				gameUI.handlePauseMouse(mousePos, paused, onMenu);
			else if (!(paused && levelStart))
				gameUI.handlePreLevelMenu(mousePos, levelStart, onMenu);
		}
	}

	//===========================================================
	// Everything from here to the end of the loop is where you put your
	// code to produce ONE frame of the animation. The next iteration of the loop will
	// render the next frame, and so on. All this happens ~ 60 times/second.
	//===========================================================

	// draw background first, so everything that's drawn later 
	// will appear on top of background
	if (!paused && levelStart) {
		player.move();
		boss.updatePos();
		boss.throwMooCows(frames, enemyWeapon);
		playerWeapon.updatePos();
		hit = boss.checkBounds(playerWeapon);
		player.checkBounds(enemyWeapon);
	}
	if (hit && boss.getHealth() > 10) {
 		score += 200;
	}
	else if (hit && boss.getHealth() <= 10) {
		score += 300;
	}
	// draw the ship on top of background 
	// (the ship from previous frame was erased when we drew background)
	renderLevel(win, background);
	if (paused)
		gameUI.drawPauseMenu(win);
	else if (!levelStart)
		gameUI.drawPreLevelMenu(win);
	// end the current frame; this makes everything that we have 
	// already "drawn" actually show up on the screen

	if (boss.getHealth() == 0) {
   		levelComplete = true;
	}
	else if (boss.getHealth() <= 10) {
		boss.setDeepFried(deepFriedTexture);
		boss.setFrames(20);
	}

	return levelComplete;
}