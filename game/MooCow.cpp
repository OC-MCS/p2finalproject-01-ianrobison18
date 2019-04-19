#include <iostream>
#include "MooCow.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

/*
Name: moo (MooCow)
Purpose: moo
Parameters: moo (nothing)
Returns: moo (N/A)
*/
MooCow::MooCow() {
	
}

/*
Name: moo (MooCow)
Purpose: moo moo (initialize a moocow)
Parameters: moo (a sprite)
Returns: moo (N/A)
*/
MooCow::MooCow(Sprite &cow) {
	this->cow = cow;
}

/*
Name: moo (update position)
Purpose: mooooo (moove a moooo cow)
Parameters: moo (nothing)
Returns: moo (nothing)
*/
void MooCow::updatePosition()
{
	cow.move(0, 5);
}

/*
Name: moo (get global bounds)
Purpose: moOoOoOo (get area for cows)
Parameters: mOooo (nothing)
Returns: moo moo (bounds for cow)
*/
FloatRect MooCow::getGlobalBounds()
{
	return getMooCow().getGlobalBounds();
}

/*
Name: moo (get moocow)
Purpose: mooooooo (return the sprite_
Parameters: moo (nothing)
Returns: moooooooooooooooooooooooo (the cow)
*/
Sprite MooCow::getMooCow()
{
	return cow;
}

/*
Name: moo (set moo cow) 
Purpose: mooooo (set the current sprite)
Parameters: MoOoOoOo (the sprite)
Returns: moomoo (nothing)
*/
void MooCow::setMooCow(Sprite &cow)
{
	this->cow = cow;
}

/*
Name: == operator
Purpose: to pit two moocows against each in a battle for dominance in the farm.
Only one cow shall survive, and the one that does shall take control of the farm
and establish itself as a cow among cows. Do you dare test these cows in a battle
for survival? Indeed, we must.
Parameters: a moocow to challenge the current champion
Returns: the survivor
*/
bool MooCow::operator==(MooCow compare)
{
	bool isEqual;
	if (cow.getPosition() == compare.getMooCow().getPosition())
	{
		isEqual = true;
	}
	else
	{
		isEqual = false;
	}

	return isEqual;
}