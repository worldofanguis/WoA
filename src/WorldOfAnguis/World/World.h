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
#include "Graphics/DirectX/World/DXWorldView.h"

/* TESTING ONLY */
class Explosion
{
public:
	Explosion() {}
	~Explosion() {}
private:
	
};

class World : DXWorldView
{
public:
	World();
	~World();
	
	/* Load the Map for the hittest and the Map with the texture (maybe this could be done from 1 map?) */
	bool LoadMaps(char *HitMap,char* TexturedMap);
	
	/* Call the View class draw function with the paramters */
	void Draw(int Left,int Top,int Width,int Height) {DXWorldView::Draw(Left,Top,Width,Height);}
	
	/* Deform the map */
	void Explode(Explosion* Ex);
	
	/* Get map infos */
	char* GetHitMap() {return Map;}
	int GetPixelPerHitMap() {return PPHM;}
	int GetHitMapWidth() {return Width;}
	int GetHitMapHeight() {return Height;}
	
	int GetWidth() {return Width*PPHM;}
	int GetHeight() {return Height*PPHM;}
private:
	char *Map;				// HitMap //
	int MapSize;
	int PPHM;				// PixelPerHitMap //
	
	int Width;
	int Height;
};