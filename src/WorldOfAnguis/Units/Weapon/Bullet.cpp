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

Bullet::Bullet(int X,int Y,float Angle,TYPES Type) : Unit(X,Y,BULLET)
{
	BType = Type;
	
	switch(BType)
		{
		case DEFAULT:
			vX = cos(Angle)*3;
			vY = -sin(Angle)*3;
			
			Width = Height = 10;
			
			Damage = 2;
			R = 50;
		
			sDrawMgr->RegisterUnit((Unit*)this,"..\\..\\pic\\Bullet\\Def.bmp");
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
		new Explosion(X,Y,R,Damage);
		Deactivate();
		}

return false;
}
