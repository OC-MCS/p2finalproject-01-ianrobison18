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
	RectangleShape pauseMenu, 
		exitButton,
		playButton, 
		levelBox;
	Text westernSpiesLeft,
		bossLives,
		slavLives,
		score,
		pauseText,
		playText,
		exitText;
	Font font;
	int levelNum;
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