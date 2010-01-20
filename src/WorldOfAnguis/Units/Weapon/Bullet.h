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
#include "Units/Unit.h"
#include "Units/Player/Player.h"

class Bullet : public Unit
{
public:
	enum TYPES {DEFAULT};
	Bullet(Player* Creator,int X,int Y,float Angle,TYPES Type);
	~Bullet();
	
	bool CollisionWorld();
private:
	TYPES BType;
	
	int Damage;
	int R;
	
	Player* Creator;
};