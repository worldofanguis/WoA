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
 
// View for the world class -> this class is responsigble for drawing the map on the screen //

#pragma once
#include "Common.h"

class DXWorldView
{
public:
	static void SetDevice(LPDIRECT3DDEVICE9 pDevice) {DXWorldView::pDevice = pDevice;}
	static void SetBackBuffer(LPDIRECT3DSURFACE9 pBackBuffer) {DXWorldView::pBackBuffer = pBackBuffer;}

	
protected:
	/* Hide constructor/desctructor because its an abstract class */
	DXWorldView();
	~DXWorldView();
	/* Load the map texture from file */
	bool LoadWorldTexture(char *File);
	/* Copy the pSurface (Terrain) to the BackBuffer */
	void Draw(int Left,int Top,int Width,int Height);
	/* Updates the pSurface (Terrain), should be called after exlosions */ 
	void UpdateSurface(char *Map);
	
	int GetSurfaceWidth() {return SurfaceWidth;}
	int GetSurfaceHeight() {return SurfaceHeight;}
	
	
	int SurfaceWidth,SurfaceHeight;
	
	LPDIRECT3DSURFACE9 pSurface;				// Active map texture //
	LPDIRECT3DSURFACE9 pOriginalSurface;		// Original map texture //
	
	/* Static stuff for drawing (all instances uses the same) */
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECT3DSURFACE9 pBackBuffer;

};