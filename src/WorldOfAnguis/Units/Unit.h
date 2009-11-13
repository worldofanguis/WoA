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
	enum TYPES {PLAYER};
	/* Updates the Unit position, this func should call the HitTest and calc all the physic */
	bool Update();
	bool IsActive() {return Active;}
	
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	TYPES GetType() {return Type;}
	int GetX() {return X;}
	int GetY() {return Y;}
	
	/* Save the world pointer for collision detection */
	static void RegisterWorld(World* world) {Unit::world = world;}
	static void UnRegisterWorld() {Unit::world = NULL;}

	virtual ~Unit();
protected:
	/* We dont want this class to be created */
	Unit(TYPES Type);

	static World* world;	// World pointer (requied for hittest) // 
	
	int X,Y;		// Position //
	int vX,vY;		// Velocity //

	int Width;		// Size of the Unit //
	int Height;
	
	bool FaceRight;
	
	bool Active;
private:
	TYPES Type;
};

