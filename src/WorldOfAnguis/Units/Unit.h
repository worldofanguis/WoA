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

#define GRAVITY 0.4
#define MAXSTEEP 4

class Unit
{
public:
	enum TYPES {PLAYER,BULLET,PICKUP,EXPLOSION};

	enum STATE {STATE_ACTIVE,						// STATE_ACTIVE: The object interaction is active (collision)
				STATE_GRAPHICS_ONLY,				// STATE_GRAPHICS_ONLY: The object is only drawn (no collision)
				STATE_INACTIVE						// STATE_INACTIVE: The object will be deleted in the next frame
			   };
	
	STATE GetState() {return State;}
	void SetState(STATE state) {State = state;}

	void Update();		// Atm useless //
	
	virtual bool CollisionWorld();
	virtual bool CollisionUnit(Unit* unit);
	
	bool Collide();
	virtual bool CollideX(int* xreturn);
	bool CollideY(int* yreturn);
	bool CollidePlayerPoint(int x, int y, int* xf, int* yf);
	bool CollidePoint(int x_rel, int y_rel, int* xf, int* yf);
	bool HitTest(int x, int y);
	bool HitTestBorder(int x, int y, bool right, bool down);

	
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	TYPES GetType() {return Type;}
	int GetX() {return X;}
	int GetY() {return Y;}
	
	virtual void Explode(Unit* explosion) {}
	
	virtual ~Unit();
protected:
	/* We dont want this class to be created */
	Unit(int X,int Y,TYPES Type);
	
	int X,Y;		// Position //
	int vX,vY;		// Velocity //
	double vXd, vYd; //Double type Velocity//

	int Width;		// Size of the Unit //
	int Height;
	
	bool FaceRight;
private:
	TYPES Type;
	STATE State;
};

