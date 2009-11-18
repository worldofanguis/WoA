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

class DXHUDView : public Singleton<DXHUDView>
{
public:
	enum HUD_PART {HUD_LIFE,HUD_WEAPON};
	
	DXHUDView();
	~DXHUDView();
	
	void Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite) {this->pDevice = pDevice; this->pSprite = pSprite; LoadTexture();}

	void Draw();
	void Update(HUD_PART Part,int Data);
private:
	void LoadTexture();

	/* Texture for the HUD frame */
	LPDIRECT3DTEXTURE9 pHUD;
	/* Texture for the life bar */
	LPDIRECT3DTEXTURE9 pLifeBar;
	RECT rLifeBar;

	LPDIRECT3DDEVICE9 pDevice;
	LPD3DXSPRITE pSprite;
};

#define sHudView DXHUDView::Instance()