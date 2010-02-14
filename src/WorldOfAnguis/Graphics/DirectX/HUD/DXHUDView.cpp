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

#define HUD_LIFEBAR_X_OFFSET 49
#define HUD_LIFEBAR_Y_OFFSET 24
#define HUD_SCORE_X_OFFSET 70
#define HUD_SCORE_Y_OFFSET 95
#define HUD_MAP_X_OFFSET 800
#define HUD_MAP_Y_OFFSET 15
#define HUD_MAP_X_SIZE 200.0f
#define HUD_MAP_Y_SIZE 100.0f

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
	SAFE_RELEASE(pFont);
	SAFE_RELEASE(pHUD);
	SAFE_RELEASE(pLifeBar);
}

void DXHUDView::Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite)
{
	this->pDevice = pDevice;
	this->pSprite = pSprite;

	HUDStartY = sDXInterface->GetViewHeight();
	
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

	D3DXVECTOR3 v(0,HUDStartY,0);
	pSprite->Draw(pHUD,NULL,NULL,&v,0xFFFFFFFF);

	v = D3DXVECTOR3(HUD_LIFEBAR_X_OFFSET,HUDStartY+HUD_LIFEBAR_Y_OFFSET,0);
	pSprite->Draw(pLifeBar,&rLifeBar,NULL,&v,0xFFFFFFFF);

	D3DXMATRIX scalematrix;
	D3DXVECTOR2 scale(HUD_MAP_X_SIZE/sWorldView->GetSurfaceWidth(),HUD_MAP_Y_SIZE/sWorldView->GetSurfaceHeight());
	v = D3DXVECTOR3(HUD_MAP_X_OFFSET/scale.x,(HUDStartY+HUD_MAP_Y_OFFSET)/scale.y,0);
	pSprite->SetTransform(D3DXMatrixTransformation2D(&scalematrix,NULL,0,&scale,NULL,0,NULL));
	pSprite->Draw(sWorldView->GetDisplaySurface(),NULL,NULL,&v,0xFFFFFFFF);
	pSprite->SetTransform(D3DXMatrixIdentity(&scalematrix));

	RECT r = {HUD_SCORE_X_OFFSET,HUDStartY+HUD_SCORE_Y_OFFSET,0,0};
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
