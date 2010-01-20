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
#include "Units/Unit.h"
#include "Units/Player/Player.h"

class Explosion : public Unit
{
public:
	Explosion(Player* Creator,int X,int Y,int R,int Damage);
	~Explosion();
	
	char* GetExplosionMap();
	int GetRadius() {return radius;}
	int GetDamage() {return Damage;}
	Player* GetCreator() {return Creator;}
private:
	int radius;
	int Damage;
	char* Map;
	
	Player* Creator;
};