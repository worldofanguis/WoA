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


class DXHUDView
{
private:
	/* Static functions for setting the requied stuffs (Device & Sprite) */
	static void SetDevice(LPDIRECT3DDEVICE9 pDevice) {DXHUDView::pDevice = pDevice;}
	static void SetSprite(LPD3DXSPRITE pSprite) {DXHUDView::pSprite = pSprite;}

protected:
	enum HUD_PART {HUD_LIFE,HUD_WEAPON};
	DXHUDView();
	~DXHUDView();
	
	void LoadTexture();
	
	void Draw();
	void Update(HUD_PART Part,int Data);
private:

	/* Texture for the HUD frame */
	LPDIRECT3DTEXTURE9 pHUD;
	/* Texture for the life bar */
	LPDIRECT3DTEXTURE9 pLifeBar;
	RECT rLifeBar;

	/* Static stuff for drawing (all instances uses the same) */
	static LPDIRECT3DDEVICE9 pDevice;
	static LPD3DXSPRITE pSprite;
	
	
};