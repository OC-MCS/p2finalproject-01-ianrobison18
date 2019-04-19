#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "WesternSpies.h"
#include "Boris.h"
#include "Slav.h"

class UI
{
private:
	RectangleShape pauseMenu, // pause menu bos
		exitButton, // exit button
		playButton, // play button
		levelBox; // level info boss
	Text westernSpiesLeft, // text showing spies left
		bossLives, // text showing boss lives
		slavLives, // text showing player lives
		score, // current score text
		pauseText, // text showing that you're paused
		playText, // text for play button
		exitText; // text for exiting level or game
	Font font; // font for the game
	int levelNum; // for which level you're on
public:
	UI();
	int getLevel();
	void setLevel(int level);
	void drawPreLevelMenu(RenderWindow &win);
	void handlePreLevelMenu(Vector2f, bool &levelStart, bool &menu);
	void pauseMenuMouse(Vector2f pos);
	void drawPauseMenu(RenderWindow &win);
	void handlePauseMouse(Vector2f pos, bool &pause, bool &menu);
	void mainMenuMouse(Vector2f pos);
	void drawMainMenu(RenderWindow &win, Sprite mainMenu);
	void handleMainMenuMouse(Vector2f mouse, bool &menu, bool &close);
	void drawLevelText(RenderWindow &win, WesternSpies spies, Slav player, int score);
	void drawBossText(RenderWindow &win, Boris boss, Slav player, int points);
	void displayEndingScreen(RenderWindow &win, Sprite endScreen, int score);
	void endingScreenMouse(Vector2f mouse);
	void handleEndingScreen(Vector2f mouse, bool &gameComplete, bool &onMenu);
	void displayFailScreen(RenderWindow &win, Sprite failScreen);
	void failScreenMouse(Vector2f mouse);
	void handleFailScreen(Vector2f mouse, bool &onMenu, bool &restart);
};