/*
 * ___            ___       __
 * \  \          /  /      /  \
 *  \  \        /  /      /    \
 *   \  \  /\  /  /___   /  /\  \
 *    \  \/  \/  /|   | /  ____  \
 *     \___/\___/ |___|/__/    \__\
 *                    World Of Anguis
 *
 */
 
#pragma once
#include "Common.h"

class Unit
{
public:
	/* Updates the Unit position, this func should call the HitTest and calc all the physic */
	void Update();
	/* Virtual function for drawing */
	virtual void Draw(int ViewX,int ViewY) = 0;
	
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	int GetX() {return X;}
	int GetY() {return Y;}

protected:
	/* We dont want this class to be created */
	Unit();
	~Unit();

	/* Function for checking if we truly can move there (TODO: this wont work this way, should this be moved to the update?) */
	bool HitTest();

	int X,Y;		// Position //
	int vX,vY;		// Velocity //
	int aX,aY;		// Acceleration //

	int Width;		// Size of the Unit //
	int Height;

};

