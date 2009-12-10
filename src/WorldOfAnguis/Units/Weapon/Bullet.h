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
#include "../Unit.h"

class Bullet : public Unit
{
public:
	enum TYPES {DEF};
	Bullet(int X,int Y,float Angle,TYPES Type);
	~Bullet();
	
	bool CollisionWorld();
private:
	TYPES BType;
	
	int Damage;
	int R;
};