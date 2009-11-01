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
	
	void LoadMaps(char *HitMap,char* TexturedMap);
	
	void Draw(int Left,int Top,int Width,int Height) {DXWorldView::Draw(Left,Top,Width,Height);}
	int GetWidth() {return DXWorldView::GetSurfaceWidth();}
	int GetHeight() {return DXWorldView::GetSurfaceHeight();}
private:
	char *Map;			// 1 entry represends 2x2 pixels // Pixel = Map[X+(Y*Width)] //

};