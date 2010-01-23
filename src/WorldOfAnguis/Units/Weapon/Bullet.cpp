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


#include "Bullet.h"
#include "Units/Explosion/Explosion.h"
#include "Graphics/DirectX/DirectXInterface.h"

Bullet::Bullet(Player* Creator,int X,int Y,float Angle,TYPES Type) : Unit(X,Y,BULLET)
{
	this->Creator = Creator;
	BType = Type;
	
	switch(BType)
		{
		case DEFAULT:
			vX = cos(Angle)*3;
			vY = -sin(Angle)*3;
			
			Width = Height = 10;
			
			Damage = 2;
			R = 50;
		
			sDrawMgr->RegisterUnit((Unit*)this,"..\\..\\pic\\Bullet\\Def.bmp",UnitDrawInfo::REMOVE_NEVER);
			break;
		}
	
}
 
Bullet::~Bullet()
{
}

bool Bullet::CollisionWorld()
{
	if(Unit::CollisionWorld())
		{
		new Explosion(Creator,X,Y,R,Damage);
		SetState(Unit::STATE_INACTIVE);		// Inactive means, ready to be removed at next frame //
		}

return false;
}

bool Bullet::CollisionUnit(Unit* unit)
{
	if(Unit::CollisionUnit(unit) && unit->GetType() != Unit::EXPLOSION)		// Bullet<->Explosion collision disabled //
		{
		new Explosion(Creator,X,Y,R,Damage);
		SetState(Unit::STATE_INACTIVE);
		}

return false;
}