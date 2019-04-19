#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "UI.h"
#include "Slav.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int thickness = 2;

/*
Name: UI 
Purpose: default constructor
Parameters: nothing
Returns: N/A
*/
UI::UI() {
	levelNum = 1;

	// Pause Menu initializing
	Vector2f size(400, 250);
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	pauseMenu.setFillColor(Color::Black);
	pauseMenu.setPosition(200, 125);
	pauseMenu.setSize(size);
	pauseMenu.setOutlineThickness(thickness);
	pauseMenu.setOutlineColor(Color::White);
	pauseText.setFont(font);
	pauseText.setFillColor(Color::White);
	pauseText.setOutlineColor(Color::White);
	pauseText.setCharacterSize(25);

	size.x = 300;
	size. y = 70;

	// Play button initializing
	playButton.setFillColor(Color::White);
	playButton.setSize(size);
	playButton.setOutlineThickness(thickness);
	playButton.setOutlineColor(Color::Blue);
	playText.setFont(font);
	playText.setFillColor(Color::Blue);
	playText.setOutlineColor(Color::White);
	playText.setCharacterSize(20);

	//exit Button initializing
	exitButton.setFillColor(Color::White);
	exitButton.setSize(size);
	exitButton.setOutlineThickness(thickness);
	exitButton.setOutlineColor(Color::Blue);
	exitText.setFont(font);
	exitText.setFillColor(Color::Blue);
	exitText.setOutlineColor(Color::White);
	exitText.setCharacterSize(20);
}

/*
Name: get level
Purpose: get the level number
Parameters: nothing
Returns: the level
*/
int UI::getLevel() {
	return levelNum;
}

/*
Name: set level
Purpose: set current level
Parameters: level
Returns: nothing
*/
void UI::setLevel(int level) {
	this->levelNum = level;
}

/*
Name: draw pre level menu
Purpose: draw menu that appears before level starts
Parameters: window
Returns: nothing
*/
void UI::drawPreLevelMenu(RenderWindow &win) {
	pauseText.setPosition(355, 150);
	pauseText.setString("Ready?");
	playButton.setPosition(250, 200);
	playText.setPosition(353, 220);
	playText.setString("Play Level");
	exitButton.setPosition(250, 290);
	exitText.setString("Exit Game");
	exitText.setPosition(350, 310);

	win.draw(pauseMenu);
	win.draw(pauseText);
	win.draw(playButton);
	win.draw(playText);
	win.draw(exitButton);
	win.draw(exitText);
}

/*
Name: handle prelevel menu
Purpose: to handle your selection
Parameters: mouse pos, bools handling selection
Returns: nothing
*/
void UI::handlePreLevelMenu(Vector2f mouse, bool &levelStart, bool &menu) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		levelStart = true;
	}
	else if (exitButton.getGlobalBounds().contains(mouse)) {
		menu = true;
	}
}

/*
Name: pause menu mouse
Purpose: show which button your mouse is over
Parameters: mouse pos
Returns: nothing
*/
void UI::pauseMenuMouse(Vector2f mouse) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		playButton.setFillColor(Color::Blue);
		playText.setFillColor(Color::White);
	}
	else {
		playButton.setFillColor(Color::White);
		playText.setFillColor(Color::Blue);
	}
	if (exitButton.getGlobalBounds().contains(mouse)) {
		exitButton.setFillColor(Color::Blue);
		exitText.setFillColor(Color::White);
	}
	else {
		exitButton.setFillColor(Color::White);
		exitText.setFillColor(Color::Blue);
	}
}

/*
Name: handle pause mouse
Purpose: to handle your selection
Parameters: mouse pos, bools handling selection
Returns: nothing
*/
void UI::handlePauseMouse(Vector2f mouse, bool &pause, bool &menu) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		pause = false;
	}
	else if (exitButton.getGlobalBounds().contains(mouse)) {
		menu = true;
	}
}

/*
Name: draw pause menu
Purpose: draw pause menu
Parameters: window
Returns: nothing
*/
void UI::drawPauseMenu(RenderWindow &win) {
	pauseText.setPosition(345, 150);
	pauseText.setString("PAUSED");
	playButton.setPosition(250, 200);
	playText.setPosition(330, 220);
	playText.setString("Resume Game");
	exitButton.setPosition(250, 290);
	exitText.setString("Exit Level");
	exitText.setPosition(350, 310);

	win.draw(pauseMenu);
	win.draw(pauseText);
	win.draw(playButton);
	win.draw(playText);
	win.draw(exitButton);
	win.draw(exitText);
}

/*
Name: main menu mouse
Purpose: show which button your mouse is over
Parameters: mouse pos
Returns: nothing
*/
void UI::mainMenuMouse(Vector2f mouse) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		playButton.setFillColor(Color::Blue);
		playText.setFillColor(Color::White);
	}
	else {
		playButton.setFillColor(Color::White);
		playText.setFillColor(Color::Blue);
	}
	if (exitButton.getGlobalBounds().contains(mouse)) {
		exitButton.setFillColor(Color::Blue);
		exitText.setFillColor(Color::White);
	}
	else {
		exitButton.setFillColor(Color::White);
		exitText.setFillColor(Color::Blue);
	}
}

/*
Name: draw main menu
Purpose: draw main menu
Parameters: window
Returns: nothing
*/
void UI::drawMainMenu(RenderWindow &win, Sprite mainMenu) {
	playButton.setPosition(250, 250);
	playText.setPosition(350, 270);
	playText.setString("Play Game");
	exitButton.setPosition(250, 340);
	exitText.setString("Exit Game");
	exitText.setPosition(350, 360);

	win.draw(mainMenu);
	win.draw(playButton);
	win.draw(playText);
	win.draw(exitButton);
	win.draw(exitText);
}

/*
Name: handle main menu mouse
Purpose: to handle your selection
Parameters: mouse pos, bools handling selection
Returns: nothing
*/
void UI::handleMainMenuMouse(Vector2f mouse, bool &menu, bool &close) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		menu = false;
	}
	else if (exitButton.getGlobalBounds().contains(mouse)) {
		close = true;
	}
}

/*
Name: draw level text
Purpose: draw text giving info about the current level
Parameters: window
Returns: nothing
*/
void UI::drawLevelText(RenderWindow &win, WesternSpies spies, Slav player, int points) {
	// Box holding level info
	Vector2f size(WINDOW_WIDTH, 35);
	levelBox.setFillColor(Color::Black);
	levelBox.setOutlineColor(Color::White);
	levelBox.setSize(size);
	levelBox.setPosition(0, WINDOW_HEIGHT - 35);

	// Boss health info 
	westernSpiesLeft.setFillColor(Color::White);
	westernSpiesLeft.setFont(font);
	westernSpiesLeft.setString("Western Spies Left: " + to_string(spies.getNumSpies()));
	westernSpiesLeft.setCharacterSize(15);
	westernSpiesLeft.setPosition(WINDOW_WIDTH - 175, WINDOW_HEIGHT - 25);

	// Player health info
	slavLives.setFillColor(Color::White);
	slavLives.setFont(font);
	slavLives.setString("Slav Health: " + to_string(player.getLives()));
	slavLives.setCharacterSize(15);
	slavLives.setPosition(10, WINDOW_HEIGHT - 25);

	score.setFillColor(Color::White);
	score.setFont(font);
	score.setString("Score: " + to_string(points));
	score.setCharacterSize(15);
	score.setPosition(350, WINDOW_HEIGHT - 25);

	win.draw(levelBox);
	win.draw(westernSpiesLeft);
	win.draw(slavLives);
	win.draw(score);
}

/*
Name: draw boss text
Purpose: draw text giving info about the boss level
Parameters: window
Returns: nothing
*/
void UI::drawBossText(RenderWindow &win, Boris boss, Slav player, int points) {
	// Box holding level info
	Vector2f size(WINDOW_WIDTH, 35);
	levelBox.setFillColor(Color::Black);
	levelBox.setOutlineColor(Color::White);
	levelBox.setSize(size);
	levelBox.setPosition(0, WINDOW_HEIGHT - 35);

	// Boss health info 
	bossLives.setFillColor(Color::White);
	bossLives.setFont(font);
	bossLives.setString("The Slav King: " + to_string(boss.getHealth()) + "/25");
	bossLives.setCharacterSize(15);
	bossLives.setPosition(WINDOW_WIDTH - 150, WINDOW_HEIGHT - 25);

	// Player health info
	slavLives.setFillColor(Color::White);
	slavLives.setFont(font);
	slavLives.setString("Slav Health: " + to_string(player.getLives()));
	slavLives.setCharacterSize(15);
	slavLives.setPosition(10, WINDOW_HEIGHT - 25);

	score.setFillColor(Color::White);
	score.setFont(font);
	score.setString("Score: " + to_string(points));
	score.setCharacterSize(15);
	score.setPosition(350, WINDOW_HEIGHT - 25);

	win.draw(levelBox);
	win.draw(bossLives);
	win.draw(slavLives);
	win.draw(this->score);
}

/*
Name: draw ending screen
Purpose: draw screen that displays after the game is complete
Parameters: window
Returns: nothing
*/
void UI::displayEndingScreen(RenderWindow &win, Sprite endScreen, int points) {
	playButton.setPosition(250, 410);
	playText.setPosition(355, 430);
	playText.setString("Play Again");
	exitButton.setPosition(250, 500);
	exitText.setString("Exit To Menu");
	exitText.setPosition(340, 520);
	
	Vector2f size(160, 70);
	RectangleShape scoreBox;
	scoreBox.setFillColor(Color::Black);
	scoreBox.setPosition(320, 30);
	scoreBox.setSize(size);
	scoreBox.setOutlineThickness(thickness);
	scoreBox.setOutlineColor(Color::White);
	score.setFillColor(Color::White);
	score.setFont(font);
	score.setString("Score: " + to_string(points));
	score.setCharacterSize(25);
	score.setPosition(325, 50);

	win.draw(endScreen);
	win.draw(playButton);
	win.draw(playText);
	win.draw(exitButton);
	win.draw(exitText);
	win.draw(scoreBox);
	win.draw(score);
}

/*
Name: ending screen mouse
Purpose: show which button your mouse is over
Parameters: mouse pos
Returns: nothing
*/
void UI::endingScreenMouse(Vector2f mouse) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		playButton.setFillColor(Color::Blue);
		playText.setFillColor(Color::White);
	}
	else if (exitButton.getGlobalBounds().contains(mouse)) {
		playButton.setFillColor(Color::White);
		playText.setFillColor(Color::Blue);
	}
	if (exitButton.getGlobalBounds().contains(mouse)) {
		exitButton.setFillColor(Color::Blue);
		exitText.setFillColor(Color::White);
	}
	else {
		exitButton.setFillColor(Color::White);
		exitText.setFillColor(Color::Blue);
	}
}

/*
Name: handle ending screen mouse
Purpose: to handle your selection
Parameters: mouse pos, bools handling selection
Returns: nothing
*/
void UI::handleEndingScreen(Vector2f mouse, bool &close, bool &restart) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		restart = true;
	}
	else if (exitButton.getGlobalBounds().contains(mouse)) {
		close = true;
	}
}

/*
Name: draw game over screen
Purpose: draw game over screen
Parameters: window
Returns: nothing
*/
void UI::displayFailScreen(RenderWindow &win, Sprite failScreen) {
	/*playButton.setPosition(250, 230);
	playText.setPosition(353, 250);
	playText.setString("Play Again");*/
	exitButton.setPosition(250, 340);
	exitText.setString("Exit Game");
	exitText.setPosition(350, 360);

	win.draw(failScreen);
	/*win.draw(playButton);
	win.draw(playText);*/
	win.draw(exitButton);
	win.draw(exitText);
}

/*
Name: fail screen mouse
Purpose: show which button your mouse is over
Parameters: mouse pos
Returns: nothing
*/
void UI::failScreenMouse(Vector2f mouse) {
	if (playButton.getGlobalBounds().contains(mouse)) {
		playButton.setFillColor(Color::Blue);
		playText.setFillColor(Color::White);
	}
	else if (exitButton.getGlobalBounds().contains(mouse)) {
		playButton.setFillColor(Color::White);
		playText.setFillColor(Color::Blue);
	}
	if (exitButton.getGlobalBounds().contains(mouse)) {
		exitButton.setFillColor(Color::Blue);
		exitText.setFillColor(Color::White);
	}
	else {
		exitButton.setFillColor(Color::White);
		exitText.setFillColor(Color::Blue);
	}
}

/*
Name: handle fail screen mouse
Purpose: to handle your selection
Parameters: mouse pos, bools handling selection
Returns: nothing
*/
void UI::handleFailScreen(Vector2f mouse, bool &onMenu, bool &restart) {
	if (exitButton.getGlobalBounds().contains(mouse)) {
		onMenu = true;
	}
	else if (playButton.getGlobalBounds().contains(mouse)) {
		restart = true;
	}
}