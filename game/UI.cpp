#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "UI.h"

const int thickness = 2;
UI::UI()
{
	pauseMenu.setFillColor(Color::Black);
	pauseMenu.setPosition(200, 325);
	pauseMenu.setOutlineThickness(thickness);
	pauseMenu.setOutlineColor(Color::White);
}

void pauseMenuMouse(Vector2f pos);

void UI::drawPauseMenu(RenderWindow &win)
{
	win.draw(pauseMenu);
}

void mainMenuMouse(Vector2f pos);

void drawMainMenu(RenderWindow &win);

void drawLevelText(RenderWindow &win, WesternSpies spies);

void UI::drawBossText(RenderWindow &win, Boris boss)
{
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\comic.ttf");
	bossLives.setFillColor(Color::Black);
	bossLives.setFont(font);
	bossLives.setString("Boss Health");
	bossLives.setCharacterSize(15);
	bossLives.setPosition(20, 20);
	win.draw(bossLives);
}