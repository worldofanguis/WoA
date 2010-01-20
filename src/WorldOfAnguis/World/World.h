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


/* Class: World
 * Description: This class handles the hitmap (the surface - world)
 *
 * Functions: LoadMap(...)
 *				creates the hitmap from a bmp
 *			  Explode(...)
 *				this function alters the hitmap with the explosion in the parameter, and calls the UpdateSurface function
 */

#pragma once
#include "Common.h"
#include "Singleton.h"
#include "Units/Unit.h"
#include "Graphics/DirectX/World/DXWorldView.h"

class World : public Singleton<World>
{
public:
	World();
	~World();
	
	/* Load the Map for the hittest and the Map with the texture (maybe this could be done from 1 map?) */
	bool LoadMap(char *HitMap);
	
	/* Get map infos */
	char* GetHitMap() {return Map;}
	int GetPixelPerHitMap() {return PPHM;}
	int GetHitMapWidth() {return Width;}
	int GetHitMapHeight() {return Height;}
	
	int GetWidth() {return Width*PPHM;}
	int GetHeight() {return Height*PPHM;}

	void Explode(Unit* explosion);
	
	void PrintMap();

private:
	char *Map;				// HitMap //
	int MapSize;
	int PPHM;				// PixelPerHitMap //
	
	int Width;
	int Height;
};

#define sWorld World::Instance()
