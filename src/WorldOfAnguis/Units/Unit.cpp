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
#include "Units/ObjectMgr.h"

Unit::Unit(int X,int Y,TYPES Type)
{
	this->X = X;
	this->Y = Y;
	this->Type = Type;
	
	vX = vY = 0;
	Width = Height = 0;
	
	sObjMgr->RegisterUnit(this);
}

Unit::~Unit()
{
	Active = false;
}

void Unit::Update()
{
	X+=vX;
	Y+=vY;
}

bool Unit::CollisionWorld()
{
//	if(vY < 10)			// Apply gravity //
//		vY += GRAVITY;

return false;
}

bool Unit::CollisionUnit(Unit* unit)
{
	if(unit == this)	// We dont want to check collision with self ^^ //
		return false;

	int SelfCX,SelfCY,UnitCX,UnitCY;
	SelfCX = X+vX+(Width/2);
	SelfCY = Y+vY+(Height/2);
	UnitCX = unit->X+(unit->Width/2);
	UnitCY = unit->Y+(unit->Height/2);
	if((abs(SelfCX-UnitCX) < max(Width,unit->Width)) && abs(SelfCY-UnitCY) < max(Height,unit->Height))
		{
		vX = 0;			// Stop the target (at least for now) //
		vY = 0;
		return true;
		}

return false;
}

