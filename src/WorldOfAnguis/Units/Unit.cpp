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


#include "Unit.h"

World* Unit::world = NULL;

Unit::Unit(TYPES Type)
{
	X = Y = 0;
	vX = vY = 0;

	Width = Height = 0;
	
	this->Type = Type;
}

Unit::~Unit()
{

}

bool Unit::Update()
{
	if(vX == 0 && vY == 0)		// We dont move since we dont have any velocity //
		return false;
	bool Collided = false;
	X += vX;
	Y += vY;

	//char* Map = world->GetHitMap();
	//int PPHM = world->GetPixelPerHitMap();
	//int MapWidth = world->GetHitMapWidth();
	
	//int dX,dY; //new coord.


	/* kell egy külön ütközésvizsgálat, csak 1 pontra */


	//for(dX=X;dX!=X+vX;vX>0?dX++:dX--)		// increase or decrease the dX depending on we are moving left or right //
	//	{
	//	if(dX<0) {dX = 0; vX = 0; break;}
	//	else if(dX+Width>world->GetWidth()) {dX = world->GetWidth()-Width; vX = 0; break;}

	//	if(Map[((Y/PPHM)*MapWidth)+(dX/PPHM)] > 0)				// Collision along the X axis //
	//		{
	//		vX = 0;
	//		Collided = true;
	//		break;
	//		}
	//	}

	//for(dY=Y;dY!=Y+vY;vY>0?dY++:dY--)		// increase or decrease the dY depending on we are moving up or down //
	//	{
	//	if(dY<0) {dY = 0; vY = 0; break;}
	//	else if(dY+Height>world->GetHeight()) {dY = world->GetHeight()-Height; vY = 0; break;}

	//	if(Map[((dY/PPHM)*MapWidth)+(dX/PPHM)] > 0)
	//		{
	//		vY = 0;		// Hit the ground -> lost our Y velocity //
	//		Collided = true;
	//		break;
	//		}
	//	}
	
	//X = dX;
	//Y = dY;
return Collided;
}
