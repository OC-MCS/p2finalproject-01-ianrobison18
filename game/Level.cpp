#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Level.h"
#include "UI.h"

/*
Name: level
Purpose: default constructor
Parameters: nothing
Returns: N/A
*/
Level::Level(){}

/*
Name: Level
Purpose: initializes a level
Parameters: enemy texture, enemy frames, enemy speed
Returns: N/A
*/
Level::Level(Texture &enemyTexture,  int enemyFrames, float speed) {
	this->enemyTexture = enemyTexture;
	WesternSpies enemy(enemyTexture);
	enemies = enemy;
	this->speed = speed;
	this->enemyFrames = enemyFrames;
}

/*
Name: restart level
Purpose: if player dies or wants to play again, reset level
Parameters: texture to reinitialize enemies
Returns: nothing
*/
void Level::restartLevel(Texture &enemyTexture) {
	this->enemyTexture = enemyTexture;
	WesternSpies enemy(enemyTexture);
	enemies = enemy;
	enemies.setFrames(60);
	this->speed = speed;
	this->enemyFrames = enemyFrames;
}

/*
Name: render level
Purpose: draw level
Parameters: window, background
Returns: nothing
*/
void Level::renderLevel(RenderWindow &win, Sprite background) {
	win.draw(background);
	win.draw(player.getSlav());
	playerWeapon.drawBottles(win);
	enemies.drawWesternSpies(win);
	enemyWeapon.drawMooCows(win);
	gameUI.drawLevelText(win, enemies, player, score);
}

/*
Name: set background
Purpose: sets the level background
Parameters: sprite background
Returns: nothing
*/
void Level::setBackground(Sprite background) {
	this->background = background;
}

/*
Name: set score
Purpose: sets the level's current score
Parameters: the score from the previous level
Returns: nothing
*/
void Level::setScore(int score) {
	this->score = score;
}

/*
Name: get score
Purpose: get the score from that level
Parameters: nothing
Returns: the score
*/
int Level::getScore() {
	return score;
}

/*
Name: set UI
Purpose: sets the data from the UI into the level
Parameters: the UI
Returns: nothing
*/
void Level::setUI(UI ui) {
	this->gameUI = ui;
}

/*
Name: get player
Purpose: returns the player data from the level
Parameters: nothing
Returns: the player
*/
Slav Level::getPlayer() {
	return player;
}

/*
Name: set player
Purpose: initializes the player in the level
Parameters: the player
Returns: nothing
*/
void Level::setPlayer(Slav s) {
	player = s;
}

/*
Name: get player weapon
Purpose: to return the weapon
Parameters: nothing
Returns: the bottle
*/
Bottles Level::getPlayerWeapon() {
	return playerWeapon;
}

/*
Name: set player weapon
Purpose: to initialize the bottle in the level
Parameters: the bottle
Returns: nothing
*/
void Level::setPlayerWeapon(Bottles b) {
	playerWeapon = b;
}

/*
Name: get enemies
Purpose: get the enemies from the level
Parameters: nothing
Returns: the spies
*/
WesternSpies Level::getEnemies() {
	return enemies;
}

/*
Name: get enemy weapon
Purpose: get the enemy weapon from the level
Parameters: nothing
Returns: the spies' weapons
*/
MooCows Level::getEnemyWeapon() {
	return enemyWeapon;
}

/*
Name: get enemy frames
Purpose: get the enemy frames until fire from the level
Parameters: nothing
Returns: the spies' frames
*/
int Level::getEnemyFrames() {
	return enemyFrames;
}

/*
Name: set enemy weapon
Purpose: set the enemy weapon for the level
Parameters: the spies' weapons
Returns: nothing
*/
void Level::setEnemyWeapon(MooCows m) {
	enemyWeapon = m;
}

/*
Name: play level
Purpose: play the current level
Parameters: a lot of stuff
Returns: if level is complete
*/
bool Level::playLevel(RenderWindow &win, bool canFire, int frames, 
	bool &paused, bool &onMenu, bool &levelStart, bool &fail)
{
	// check all the window's events that were triggered since the last iteration of the loop
	// For now, we just need this so we can click on the window and close it
	Event event;
	bool levelComplete = false,
		hit = false;

	while (win.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Space && canFire)
			{
				// handle space bar
				Vector2f pos = player.getSlav().getPosition();
   				playerWeapon.addBottle(pos);
				canFire = false;
			}
			else if (event.key.code == Keyboard::Escape && !paused)
			{
				paused = true;
			}
			else if (event.key.code == Keyboard::Escape && paused)
			{
				paused = false;
			}
		}
		else if (event.type == Event::MouseMoved)
		{
			Vector2f mousePos = win.mapPixelToCoords(Mouse::getPosition(win));
			gameUI.pauseMenuMouse(mousePos);
			
		}
		if (event.type == Event::MouseButtonReleased)
		{
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

	if (!paused && levelStart)
	{
		player.move();
		enemies.updatePos(speed, player);
		enemies.throwMooCows(frames, enemyWeapon);
		playerWeapon.updatePos();
 		hit = enemies.checkBounds(playerWeapon);
		player.checkBounds(enemyWeapon);
	}
	if (hit)
	{
  	score += 100;
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

	if (enemies.getNumSpies() == 0)
	{
		levelComplete = true;
	}
	else if (player.getLives() == 0)
	{
		fail = true;
	}
	return levelComplete;
}