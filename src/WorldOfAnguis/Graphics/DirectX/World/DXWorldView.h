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


/* Class: DXWorldView
 * Description: The goal of this class is to draw the world, the surface on the screen
 *
 * Functions: Setup(...)
 *				setup the class with the drawing devices
 *			  LoadWorldTexture(...)
 *				load the texture of the world from a bmp file
 *			  Draw(...)
 *				draw the section of the world on the screen buffer, we are looking at
 *			  UpdateSurface(...)
 *				this function is responsible for reshaping the world texture after
 *				an explosion or something that alter its shape.
 */


#pragma once
#include "Common.h"
#include "Singleton.h"

class DXWorldView : public Singleton<DXWorldView>
{
public:
	DXWorldView();
	~DXWorldView();

	int GetSurfaceWidth() {return SurfaceWidth;}	// The size of the map //
	int GetSurfaceHeight() {return SurfaceHeight;}	// The size of the map //

	void Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite) {this->pDevice = pDevice; this->pSprite = pSprite;}
	
	/* Load the map texture from file */
	bool LoadWorldTexture(char *File);
	/* Copy the pSurface (Terrain) to the BackBuffer */
	void Draw(int Left,int Top,int Width,int Height);
	/* Updates the pSurface (Terrain), should be called after exlosions */ 
	void UpdateSurface(char *Map,int MapWidth,int PixelPerHitMap,RECT* DirtyRegion);
	
	LPDIRECT3DTEXTURE9 GetDisplaySurface() {return pDisplaySurface;}
private:
	int SurfaceWidth;
	int SurfaceHeight;
	int BytesPerPixel;
	
	LPDIRECT3DTEXTURE9 pDisplaySurface;			// Active map texture //
	LPDIRECT3DTEXTURE9 pWorkSurface;			// Working texture //
	LPDIRECT3DTEXTURE9 pOriginalSurface;		// Original map texture //
	
	LPDIRECT3DDEVICE9 pDevice;
	LPD3DXSPRITE pSprite;
};

#define sWorldView DXWorldView::Instance()