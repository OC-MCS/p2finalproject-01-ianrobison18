//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
#include <list>
#include <time.h>
#include "Slav.h"
#include "Bottles.h"
#include "WesternSpies.h"
#include "MooCows.h"
#include "Boris.h"
#include "Level.h"
#include "BossLevel.h"
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

//============================================================
// Ian Robison
// Programming II
// Space Shooter Game
//============================================================

bool checkFrames(int &frames, bool canFire);
void checkEnemyFrames(Level currentLevel, int &frames, int &randomNum);
void checkEnemyFrames(BossLevel currentLevel, int &frames, int &randomNum);
int randomFrames(int frames);
int main() {
	const int WINDOW_WIDTH = 800; // width of the window
	const int WINDOW_HEIGHT = 600; // height of the window
	const int FARTHEST_LEFT = 0; // how far left the player can go
	const int FARTHEST_RIGHT = WINDOW_WIDTH - 64; // how far right the player can go

	// the window for the game
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Adventures of Blyatman");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	
	Texture mainMenu; // main menu texture
	if (!mainMenu.loadFromFile("mainMenu.png")) {
		cout << "Unable to load menu texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture slavBackgroundTexture; // background texture
	if (!slavBackgroundTexture.loadFromFile("StPetersburg.png")) {
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture endingTexture; // ending screen texture
	if (!endingTexture.loadFromFile("gameEndScreen.png")) {
		cout << "Unable to load ending Screen texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture failTexture; // game over screen texture
	if (!failTexture.loadFromFile("GameOver.png")) {
		cout << "Unable to load game over texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture slavTexture; // player texture
	if (!slavTexture.loadFromFile("Slav.png")) {
		cout << "Unable to load slav texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bottleTexture; // bottle texture
	if (!bottleTexture.loadFromFile("Bottle.png")) {
		cout << "Unable to load bottle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture westernSpyTexture; // enemy texture
	if (!westernSpyTexture.loadFromFile("enemy.png")) {
		cout << "Unable to load spy texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture enemySlavTexture; // second enemy texture
	if (!enemySlavTexture.loadFromFile("enemySlav.png")) {
		cout << "Unable to load enemy Slav texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture borisTexture; // boss texture
	if (!borisTexture.loadFromFile("SlavKing.png")) {
		cout << "Unable to load Slav King texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture deepFriedTexture; // secondary boss texture
	if (!deepFriedTexture.loadFromFile("SlavKing2.png")) {
		cout << "Can't load from slavKing 2 from file.\n";
		exit(EXIT_FAILURE);
	}

	int level1Frames = 65,
		level2Frames = 50,
		bossLevelFrames = 40;
	Level levelOne(westernSpyTexture, level1Frames, 0.3f); // the first level
	Level levelTwo(enemySlavTexture, level2Frames, 0.45f); // the second level
	BossLevel slavKingFight(borisTexture, deepFriedTexture, bossLevelFrames); // the boss level
	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite menuBackground; // main menu sprite
	menuBackground.setTexture(mainMenu);
	Sprite endingBackground; // ending screen sprite
	endingBackground.setTexture(endingTexture);
	Sprite gameOver; // game ovoer screen sprite
	gameOver.setTexture(failTexture);
	Sprite background; // background sprite
	background.setTexture(slavBackgroundTexture);
	levelOne.setBackground(background);
	levelTwo.setBackground(background);
	slavKingFight.setBackground(background);

	// Slav sprite data
	Sprite slavic; // player sprite
	slavic.setTexture(slavTexture);
	float slavX = 300;
	float slavY = 500;
	slavic.setPosition(slavX, slavY);
	Slav slav(slavic); // the player
	levelOne.setPlayer(slav);
	levelTwo.setPlayer(slav);
	slavKingFight.setPlayer(slav);

	// Bottle data
	Bottles bottles(bottleTexture); // player weapon
	levelOne.setPlayerWeapon(bottles);
	levelTwo.setPlayerWeapon(bottles);
	slavKingFight.setPlayerWeapon(bottles);

	Music gameMusic; // in-game music
	if (!gameMusic.openFromFile("gameMusic.ogg")) {
		cout << "Unable to load in game music!" << endl;
		exit(EXIT_FAILURE);
	}

	SoundBuffer cheekiBuffer; // sound the boss says at the beginning of the level
	if (!cheekiBuffer.loadFromFile("cheekiBreeki.ogg")) {
		cout << "unable to load cheeki breeki!" << endl;
		exit(EXIT_FAILURE);
	}
	Sound cheekiBreeki; // sound in sound class
	cheekiBreeki.setBuffer(cheekiBuffer);
	cheekiBreeki.setVolume(100.f);
	bool playCheekiBreeki = true;
	gameMusic.setVolume(40.f);
	gameMusic.play();
	gameMusic.setLoop(true);

	int frames = 0; // initial frames for checking if play can fire
	int enemyFrames = 0; // checking if enemy can fire
	UI gameUI; // the gam ui
	gameUI.setLevel(1);

	bool canFire = true, // if can fire
		levelComplete = false, // if level complete
		paused = false, // if paused
		onMenu = true, // if on main menu
		close = false, // if player wants to close
		levelStart = false, // if level has started
		gameComplete = false, // if game is complete
		fail = false, // if you lost
		restart = false; // if you want to play again
	int score = 0, // initial score
		currentLives = 5, // current number of lives
		randomNumber1 = randomFrames(level1Frames),
		randomNumber2 = randomFrames(level2Frames),
		randomNumber3 = randomFrames(bossLevelFrames);

	while (window.isOpen()) {
		if (onMenu) {
			if (fail) {
				Slav reset(slavic);
				levelOne.setPlayer(slav);
				levelTwo.setPlayer(slav);
				slavKingFight.setPlayer(slav);
				fail = false;
				currentLives = 5;
			}
			gameUI.drawMainMenu(window, menuBackground);
			Event event;
			if (close == true) {
				window.close();
			}
			while (window.pollEvent(event)) {
				if (event.type == Event::MouseMoved) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					gameUI.mainMenuMouse(mousePos);

				}
				if (event.type == Event::MouseButtonReleased) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					gameUI.handleMainMenuMouse(mousePos, onMenu, close);
				}
			}
		}
		else if (!(gameComplete || fail)) {
			canFire = checkFrames(frames, canFire);

			if (gameUI.getLevel() == 1) {
				levelComplete = levelOne.playLevel(window, canFire, enemyFrames, 
					paused, onMenu, levelStart, fail);
				
				checkEnemyFrames(levelOne, enemyFrames, randomNumber1);
				if (levelComplete) {
					gameUI.setLevel(gameUI.getLevel() + 1);
					levelStart = false;
					score = levelOne.getScore();
					levelTwo.setScore(score);
					currentLives = 5;
				}
				else if (levelOne.getPlayer().getLives() < currentLives && currentLives != 0) {
					levelOne.restartLevel(westernSpyTexture);
					currentLives--;
				}
			}
			else if (gameUI.getLevel() == 2) {
				levelComplete = levelTwo.playLevel(window, canFire, enemyFrames,
					paused, onMenu, levelStart, fail);
				checkEnemyFrames(levelTwo, enemyFrames, randomNumber2);
				if (levelComplete) {
					gameUI.setLevel(gameUI.getLevel() + 1);
					levelStart = false;
					score = levelTwo.getScore();
					slavKingFight.setScore(score);
					currentLives = 5;
				}
				else if (levelTwo.getPlayer().getLives() < currentLives) {
					levelTwo.restartLevel(westernSpyTexture);
					currentLives--;
				}
			}
			else if (gameUI.getLevel() == 3) {
				cheekiBreeki.play();
				playCheekiBreeki = false;
				levelComplete = slavKingFight.playLevel(window, canFire, enemyFrames, 
					paused, onMenu, levelStart, fail);
				checkEnemyFrames(slavKingFight, enemyFrames, randomNumber3);
				if (levelComplete) {
					levelStart = false;
					gameComplete = true;
					score += slavKingFight.getScore();
				}
				else if (slavKingFight.getPlayer().getLives() < currentLives) {
					slavKingFight.restartLevel(slavTexture, deepFriedTexture);
					currentLives--;
				}
			}
			// At this point the frame we have built is now visible on screen.
			// Now control will go back to the top of the animation loop
			// to build the next frame. Since we begin by drawing the
			// background, each frame is rebuilt from scratch.
		}
		else if (gameComplete) {
			Event event;
			gameUI.displayEndingScreen(window, endingBackground, score);
			while (window.pollEvent(event)){
				if (event.type == Event::MouseMoved) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					gameUI.endingScreenMouse(mousePos);
				}
				if (event.type == Event::MouseButtonReleased) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					gameUI.handleEndingScreen(mousePos, close, restart);
				}
			}
			if (restart) {
				gameComplete = false;
				gameUI.setLevel(1);
				levelOne.restartLevel(westernSpyTexture);
				levelTwo.restartLevel(westernSpyTexture);
				slavKingFight.restartLevel(slavTexture, deepFriedTexture);
			}
			else if (close) {
				window.close();
			}
		}
		if (fail) {
			Event event;
			gameUI.displayFailScreen(window, gameOver);
			while (window.pollEvent(event)) {
				if (event.type == Event::MouseMoved) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					gameUI.failScreenMouse(mousePos);
				}
				if (event.type == Event::MouseButtonReleased) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					gameUI.handleFailScreen(mousePos, onMenu, restart);
				}
			}
		}
		window.display();
   	} // end body of animation loop

	return 0;
}

/*
Name: check frames
Purpose: checks to see if player can fire
Parameters: current frame, if player can fire
Returns: if player can fire
*/
bool checkFrames(int &frames, bool canFire) {
	frames++;
	if (frames == 60) {
		frames = 0;
	}
	if (frames % 15 == 0) {
		canFire = true;
	}

	return canFire;
}

/*
Name: check enemy frames
Purpose: resets enemy frames so that the value doesn't get too high for the int
Parameters: level, enemy frames
Returns: nothing
*/
void checkEnemyFrames(Level currentLevel, int &frames, int &randomNum) {
	frames++;
	if (frames == randomNum) {
		frames = 0;
		randomNum = randomFrames(randomNum);
	}
}

/*
Name: check enemy frames
Purpose: overloaded function for boss level
Parameters: level, enemy frames
Returns: nothing
*/
void checkEnemyFrames(BossLevel currentLevel, int &frames, int &randomNum) {
	frames++;
	if (frames == randomNum) {
		frames = 0;
		randomNum = randomFrames(randomNum);
	}
}

/*
Name: random frames
Purpose: gets random frames for  enemy fire
Parameters: frames
Returns: the frames
*/
int randomFrames(int frames)
{
	int lowerbound = frames / 2;
	srand(time(0));
	int randomFrames = rand() % frames + lowerbound;
	return randomFrames;
}