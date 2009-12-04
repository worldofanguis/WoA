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

class Explosion : public Unit
{
public:
	Explosion(int X,int Y,int R,int Damage);
	~Explosion();
	
	char* GetExplosionMap();
	int GetRadius() {return radius;}
	
private:
	int radius;
	int Damage;
	char* Map;
	
/*

00100
01110
11111
01110
00100

0010001110111110111000100

*/
};