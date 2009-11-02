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
#include "Graphics/World/DXWorldView.h"

class World : DXWorldView
{
public:
	World();
	~World();
	
	/* Load the Map for the hittest and the Map with the texture (maybe this could be done from 1 map?) */
	void LoadMaps(char *HitMap,char* TexturedMap);
	
	/* Call the View class draw function with the paramters */
	void Draw(int Left,int Top,int Width,int Height) {DXWorldView::Draw(Left,Top,Width,Height);}
	
	/* Get the map size */
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
private:
	char *Map;			// TODO: [decide the formula] ; 1 entry represends 2x2 pixels // Pixel = Map[X+(Y*Width)] //
	int MapSize;
	
	int Width;
	int Height;
};