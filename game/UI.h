#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "WesternSpies.h"
#include "Boris.h"

class UI
{
private:
	RectangleShape pauseMenu,
		resumeButton, exitButton,
		playButton;
	Text westernSpiesLeft,
		bossLives,
		slavLives;
public:
	UI();
	void pauseMenuMouse(Vector2f pos);
	void drawPauseMenu(RenderWindow &win);
	void mainMenuMouse(Vector2f pos);
	void drawMainMenu(RenderWindow &win);
	void drawLevelText(RenderWindow &win, WesternSpies spies);
	void drawBossText(RenderWindow &win, Boris boss);
};