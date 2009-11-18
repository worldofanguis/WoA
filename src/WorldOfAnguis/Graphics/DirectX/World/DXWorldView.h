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
#include "Singleton.h"

class DXWorldView : public Singleton<DXWorldView>
{
public:
	DXWorldView();
	~DXWorldView();

	int GetSurfaceWidth() {return SurfaceWidth;}	// The size of the map //
	int GetSurfaceHeight() {return SurfaceHeight;}	// The size of the map //

	/* Load the map texture from file */
	bool LoadWorldTexture(char *File);
	/* Copy the pSurface (Terrain) to the BackBuffer */
	void Draw(int Left,int Top,int Width,int Height);
	/* Updates the pSurface (Terrain), should be called after exlosions */ 
	void UpdateSurface(char *Map,int MapWidth,int PixelPerHitMap);

	void Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite) {this->pDevice = pDevice; this->pSprite = pSprite;}
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