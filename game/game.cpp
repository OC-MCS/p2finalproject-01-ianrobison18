//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
#include <list>
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

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FARTHEST_LEFT = 0;
const int FARTHEST_RIGHT = WINDOW_WIDTH - 64;

//============================================================
// Ian Robison
// Programming II
// Space Shooter Game
//============================================================

bool checkFrames(int &frames, bool canFire);
void checkEnemyFrames(Level currentLevel, int &frames);
void checkEnemyFrames(BossLevel currentLevel, int &frames);
int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Adventures of Blyatman");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	
	Texture mainMenu;
	if (!mainMenu.loadFromFile("mainMenu.png")) {
		cout << "Unable to load menu texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture starsTexture;
	if (!starsTexture.loadFromFile("StPetersburg.png")) {
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture endingTexture;
	if (!endingTexture.loadFromFile("gameEndScreen.png")) {
		cout << "Unable to load ending Screen texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture failTexture;
	if (!failTexture.loadFromFile("GameOver.png")) {
		cout << "Unable to load game over texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture slavTexture;
	if (!slavTexture.loadFromFile("Slav.png")) {
		cout << "Unable to load slav texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bottleTexture;
	if (!bottleTexture.loadFromFile("Bottle.png")) {
		cout << "Unable to load bottle texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture westernSpyTexture;
	if (!westernSpyTexture.loadFromFile("enemy.png")) {
		cout << "Unable to load spy texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture enemySlavTexture;
	if (!enemySlavTexture.loadFromFile("enemySlav.png")) {
		cout << "Unable to load enemy Slav texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture borisTexture;
	if (!borisTexture.loadFromFile("SlavKing.png")) {
		cout << "Unable to load Slav King texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture deepFriedTexture;
	if (!deepFriedTexture.loadFromFile("SlavKing2.png")) {
		cout << "Can't load from slavKing 2 from file.\n";
		exit(EXIT_FAILURE);
	}

	Level levelOne(westernSpyTexture, 80, 0.3f);
	Level levelTwo(enemySlavTexture, 60, 0.45f);
	BossLevel slavKingFight(borisTexture, deepFriedTexture, 45);
	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite menuBackground;
	menuBackground.setTexture(mainMenu);
	Sprite endingBackground;
	endingBackground.setTexture(endingTexture);
	Sprite gameOver;
	gameOver.setTexture(failTexture);
	Sprite background;
	background.setTexture(starsTexture);
	levelOne.setBackground(background);
	levelTwo.setBackground(background);
	slavKingFight.setBackground(background);

	// Slav sprite data
	Sprite slavic;
	slavic.setTexture(slavTexture);
	float slavX = 300;
	float slavY = 500;
	slavic.setPosition(slavX, slavY);
	Slav slav(slavic);
	levelOne.setPlayer(slav);
	levelTwo.setPlayer(slav);
	slavKingFight.setPlayer(slav);

	// Bottle data
	Bottles bottles(bottleTexture);
	levelOne.setPlayerWeapon(bottles);
	levelTwo.setPlayerWeapon(bottles);
	slavKingFight.setPlayerWeapon(bottles);

	Music gameMusic;
	if (!gameMusic.openFromFile("gameMusic.ogg")) {
		cout << "Unable to load in game music!" << endl;
		exit(EXIT_FAILURE);
	}

	SoundBuffer cheekiBuffer;
	if (!cheekiBuffer.loadFromFile("cheekiBreeki.ogg")) {
		cout << "unable to load cheeki breeki!" << endl;
		exit(EXIT_FAILURE);
	}
	Sound cheekiBreeki;
	cheekiBreeki.setBuffer(cheekiBuffer);
	cheekiBreeki.setVolume(100.f);
	bool playCheekiBreeki = true;
	gameMusic.setVolume(40.f);
	gameMusic.play();
	gameMusic.setLoop(true);

	int frames = 0;
	int enemyFrames = 0;
	UI gameUI;
	gameUI.setLevel(1);

	bool canFire = true,
		levelComplete = false,
		paused = false,
		onMenu = true,
		close = false,
		levelStart = false,
		gameComplete = false,
		fail = false,
		restart = false;
	int score = 0,
		currentLives = 5;

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
				
				checkEnemyFrames(levelOne, enemyFrames);
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
				checkEnemyFrames(levelTwo, enemyFrames);
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
				checkEnemyFrames(slavKingFight, enemyFrames);
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

void checkEnemyFrames(Level currentLevel, int &frames) {
	frames++;
	if (frames == currentLevel.getEnemyFrames()) {
		frames = 0;
	}
}

void checkEnemyFrames(BossLevel currentLevel, int &frames) {
	frames++;
	if (frames == currentLevel.getEnemyFrames()) {
		frames = 0;
	}
}