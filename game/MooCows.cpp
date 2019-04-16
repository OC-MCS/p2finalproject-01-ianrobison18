#pragma once
#include <iostream>
#include <list>
#include "MooCow.h"
#include "MooCows.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

MooCows::MooCows()
{
	if (!cowTexture.loadFromFile("mooCow.png"))
	{
		cout << "Unable to load mooCow texture!" << endl;
		exit(EXIT_FAILURE);
	}
}

MooCows::MooCows(Texture enemyTexture)
{
	if (!enemyTexture.loadFromFile("mooCow.png"))
	{
		cout << "Unable to load mooCow texture!" << endl;
		exit(EXIT_FAILURE);
	}
	cowTexture = enemyTexture;
}

list<MooCow*> MooCows::getMooCows()
{
	return cows;
}

void MooCows::setTexture(Texture enemyTexture)
{
	cowTexture = enemyTexture;
}

void MooCows::addMooCow(Vector2f pos)
{
	Sprite cow;
	cow.setPosition(pos);
	cow.setTexture(cowTexture);

	MooCow *deathIncarnate = new MooCow;
	deathIncarnate->setMooCow(cow);
	cows.push_back(deathIncarnate);
}

void MooCows::updatePos()
{
	list<MooCow*>::iterator iter;

	for (iter = cows.begin(); iter != cows.end(); )
	{
		(*iter)->updatePosition();
		Vector2f pos = (*iter)->getMooCow().getPosition();
		if (pos.y >= 1000)
		{
			iter = cows.erase(iter);
		}
		else
			iter++;
	}
}

void MooCows::drawMooCows(RenderWindow &win)
{
	list<MooCow*>::iterator iter;

	for (iter = cows.begin(); iter != cows.end(); iter++)
	{
		win.draw((*iter)->getMooCow());
	}
}
