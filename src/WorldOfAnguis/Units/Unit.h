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

#define GRAVITY 2

class Unit
{
public:
	enum TYPES {PLAYER,BULLET,PICKUP,};
	
	bool IsActive() {return Active;}
	/* Updates the Unit position should be called after collision detections */
	virtual void Update();
	
	virtual bool CollisionWorld();
	virtual bool CollisionUnit(Unit* unit);
	
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	TYPES GetType() {return Type;}
	int GetX() {return X;}
	int GetY() {return Y;}
	
	virtual ~Unit();
protected:
	/* We dont want this class to be created */
	Unit(TYPES Type);

	int X,Y;		// Position //
	int vX,vY;		// Velocity //

	int Width;		// Size of the Unit //
	int Height;
	
	bool FaceRight;
	
	bool Active;
private:
	TYPES Type;
};

