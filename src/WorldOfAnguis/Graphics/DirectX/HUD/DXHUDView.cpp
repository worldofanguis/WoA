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
#include "Units/ObjectMgr.h"
#include "../DirectXInterface.h"

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

void DXHUDView::Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite)
{
	this->pDevice = pDevice;
	this->pSprite = pSprite;
	
	D3DXCreateFont(pDevice,21,0,FW_BOLD,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Arial",&pFont);

	LoadTexture();
}

void DXHUDView::LoadTexture()
{
	if(pHUD != NULL)
		return;
	D3DXCreateTextureFromFileEx(DXHUDView::pDevice,				// Device
								"..\\..\\pic\\HUD\\HUD.bmp",
								1024,								// Width
								125,								// Height
								1,
								D3DPOOL_DEFAULT,
								D3DFMT_A8R8G8B8,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_XRGB(255,0,255),		// pink = transparent
								NULL,
								NULL,
								&pHUD);

	D3DXCreateTextureFromFileEx(DXHUDView::pDevice,				// Device
								"..\\..\\pic\\HUD\\HUD_LifeBar.bmp",
								300,								// Width
								15,									// Height
								1,
								D3DPOOL_DEFAULT,
								D3DFMT_A8R8G8B8,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_XRGB(255,0,255),		// pink = transparent
								NULL,
								NULL,
								&pLifeBar);
}

void DXHUDView::Draw()
{
	if(pHUD == NULL || pSprite == NULL)
		return;

	D3DXVECTOR3 v(0,sDXInterface->GetViewHeight(),0);
	pSprite->Draw(pHUD,NULL,NULL,&v,0xFFFFFFFF);
	v = D3DXVECTOR3(49,v.y+24,0);
	pSprite->Draw(pLifeBar,&rLifeBar,NULL,&v,0xFFFFFFFF);
	
	RECT r = {70,sDXInterface->GetViewHeight()+95,0,0};
	sprintf_s(ScoreText,sizeof(ScoreText),"%d",sObjMgr->Me()->GetScore());
	pFont->DrawText(NULL,ScoreText,-1,&r,DT_LEFT|DT_NOCLIP,0xFF000000);
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
