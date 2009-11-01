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
 
// View for the player class -> this class is responsigble for drawing the player on the screen //

#pragma once
#include "Common.h"

class DXPlayerView
{
public:
	static void SetDevice(LPDIRECT3DDEVICE9 pDevice) {DXPlayerView::pDevice = pDevice;}
	static void SetSprite(LPD3DXSPRITE pSprite) {DXPlayerView::pSprite = pSprite;}

	
protected:
	/* Hide constructor/desctructor because its an abstract class */
	DXPlayerView();
	~DXPlayerView();
	
	/* Draws the player on the X,Y coords */
	void Draw(int X,int Y);
	
private:
	void LoadTexture(int TextureID);
	
	
	int AnimationFrame;

	/* Texture for the player */
	LPDIRECT3DTEXTURE9 pTexture;
	/* Static stuff for drawing (all instances uses the same) */
	static LPDIRECT3DDEVICE9 pDevice;
	static LPD3DXSPRITE pSprite;
};
