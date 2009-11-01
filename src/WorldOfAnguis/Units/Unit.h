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
	void Update();
	virtual void Draw(int VX,int VY) = 0;
	
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	int GetX() {return X;}
	int GetY() {return Y;}

protected:
	Unit();
	~Unit();

	bool HitTest();

	int X,Y;
	int vX,vY;
	int aX,aY;

	int Width;
	int Height;

};

