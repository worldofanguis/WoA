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
	DXHUDView();
	~DXHUDView();
	
	
	void Draw(int Health,int WeaponID);
private:




	/* Static stuff for drawing (all instances uses the same) */
	static LPDIRECT3DDEVICE9 pDevice;
	static LPD3DXSPRITE pSprite;
};