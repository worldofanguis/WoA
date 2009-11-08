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
#include "World/World.h"

class Unit
{
public:
	/* Updates the Unit position, this func should call the HitTest and calc all the physic */
	bool Update();
	/* Virtual function for drawing */
	virtual void Draw(int ViewX,int ViewY) = 0;
	
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	int GetX() {return X;}
	int GetY() {return Y;}
	
	/* Save the world pointer for collision detection */
	static void RegisterWorld(World* world) {Unit::world = world;}
	static void UnRegisterWorld() {Unit::world = NULL;}

protected:
	/* We dont want this class to be created */
	Unit();
	~Unit();

	static World* world;	// World pointer (requied for hittest) // 
	
	int X,Y;		// Position //
	int vX,vY;		// Velocity //

	int Width;		// Size of the Unit //
	int Height;
	
	bool FaceRight;
};

