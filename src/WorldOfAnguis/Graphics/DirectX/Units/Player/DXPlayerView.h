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


//#pragma once
#ifndef __PlayerView__
#define __PlayerView__
#include "Common.h"
class Player;
#include "Units/Player/Player.h"

class DXPlayerView
{
public:
	DXPlayerView();
	~DXPlayerView();
	
	/* Static functions for setting the requied stuffs (Device & Sprite) */
	static void SetDevice(LPDIRECT3DDEVICE9 pDevice) {DXPlayerView::pDevice = pDevice;}
	static void SetSprite(LPD3DXSPRITE pSprite) {DXPlayerView::pSprite = pSprite;}

	/* Draws the player on the X,Y coords of the screen */
	void Draw(int X,int Y,bool FaceRight,bool Jumping);
	
private:
	/* Load the player texture based on the ID (Player<ID>.bmp) */
	void LoadTexture(int TextureID);
	
	/* The current animation frame */
	int AnimationFrame;

	/* Texture for the player */
	LPDIRECT3DTEXTURE9 pTexture;
	/* Static stuff for drawing (all instances uses the same) */
	static LPDIRECT3DDEVICE9 pDevice;
	static LPD3DXSPRITE pSprite;
};
#endif