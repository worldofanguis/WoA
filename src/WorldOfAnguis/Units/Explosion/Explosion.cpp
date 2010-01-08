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
 

#include "Explosion.h"
#include "World/World.h"

Explosion::Explosion(int X,int Y,int R,int Damage) : Unit(X-R,Y-R,EXPLOSION)
{
	this->radius = R/sWorld->GetPixelPerHitMap();
	this->Damage = Damage;
	Width = Height = radius*2;
	
	Map = new char[4*radius*radius];
	
	ZeroMemory(Map,4*radius*radius);
}

Explosion::~Explosion()
{
	delete[] Map;
}
/* TODO: FIX ME PLZ!!! */
char* Explosion::GetExplosionMap()
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	int x0=radius;
	int y0=radius;

	for(int i=x0-radius; i<x0+radius; i++){
		if(radius*2*y+i < 0 || radius*2*y+i > 4*radius*radius)
			continue;
		Map[radius*2*y+i]=1;
	}

	Map[radius]=1; 
	Map[2*radius*(2*radius-1)+radius]=1;

	while(x < y)
	{
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0) 
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		for(int i=x0-x; i<x0+x; i++){
			if(radius*2*(y0+y)+i < 0 || radius*2*(y0+y)+i > 4*radius*radius)
				continue;
			Map[radius*2*(y0+y)+i]=1;
		}

		for(int i=x0-x; i<x0+x; i++){
			if(radius*2*(y0-y)+i < 0 || radius*2*(y0-y)+i > 4*radius*radius)
				continue;
			Map[radius*2*(y0-y)+i]=1;
		}

		for(int i=x0-y; i<x0+y; i++){
			if(radius*2*(y0+x)+i < 0 || radius*2*(y0+x)+i > 4*radius*radius)
				continue;
			Map[radius*2*(y0+x)+i]=1;
		}

		for(int i=x0-y; i<x0+y; i++){
			if(radius*2*(y0-x)+i < 0 || radius*2*(y0-x)+i > 4*radius*radius)
				continue;
			Map[radius*2*(y0-x)+i]=1;
		}
	}

return Map;
}
