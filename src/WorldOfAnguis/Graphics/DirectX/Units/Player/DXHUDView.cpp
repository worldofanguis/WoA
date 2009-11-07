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


#include "DXHUDView.h"

LPDIRECT3DDEVICE9 DXHUDView::pDevice = NULL;
LPD3DXSPRITE DXHUDView::pSprite = NULL;

DXHUDView::DXHUDView()
{
	/* Max life */
	rLifeBar.top = 0;
	rLifeBar.bottom = 15;
	rLifeBar.left = 0;
	rLifeBar.right = 300;
	
	pHUD = NULL;
	pLifeBar = NULL;
	
	
}

DXHUDView::~DXHUDView()
{
}

void DXHUDView::LoadTexture()
{
	if(pHUD != NULL)
		return;
	D3DXIMAGE_INFO d3dxImageInfo;
	D3DXCreateTextureFromFileEx(DXHUDView::pDevice,				// Device
								"..\\..\\pic\\HUD\\HUD.bmp",
								1024,								// Width
								150,								// Height
								1,
								D3DPOOL_DEFAULT,
								D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(1.0f,0.0f,1.0f,1.0f),		// pink = transparent
								&d3dxImageInfo,
								NULL,
								&pHUD);

	D3DXCreateTextureFromFileEx(DXHUDView::pDevice,				// Device
								"..\\..\\pic\\HUD\\HUD_LifeBar.bmp",
								300,								// Width
								15,									// Height
								1,
								D3DPOOL_DEFAULT,
								D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(1.0f,0.0f,1.0f,1.0f),		// pink = transparent
								&d3dxImageInfo,
								NULL,
								&pLifeBar);
}

void DXHUDView::Draw()
{
	if(pHUD == NULL || pSprite == NULL)
		return;
	D3DXVECTOR3 v(0,618,0);
	pSprite->Draw(pHUD,NULL,NULL,&v,0xFFFFFFFF);
	v = D3DXVECTOR3(49,618+30,0);
	pSprite->Draw(pLifeBar,&rLifeBar,NULL,&v,0xFFFFFFFF);	
}

void DXHUDView::Update(HUD_PART Part,int Data)
{
	switch(Part)
		{
		case HUD_LIFE:
			rLifeBar.right = Data*3;
			break;
		}
		
}
