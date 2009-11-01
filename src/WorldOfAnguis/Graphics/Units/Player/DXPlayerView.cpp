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
 
 
#include "DXPlayerView.h"
#include "Graphics/DirectX/DirectXInterface.h"


LPDIRECT3DDEVICE9 DXPlayerView::pDevice = NULL;
LPD3DXSPRITE DXPlayerView::pSprite = NULL;

DXPlayerView::DXPlayerView()
{
	pTexture = NULL;
	AnimationFrame = 0;
	LoadTexture(1);
}

DXPlayerView::~DXPlayerView()
{
	SAFE_RELEASE(pTexture);
}

void DXPlayerView::LoadTexture(int TextureID)
{
	if(pTexture != NULL)
		return;
	D3DXIMAGE_INFO d3dxImageInfo;
	char File[MAX_PATH];
	sprintf_s(File,sizeof(File),"..\\..\\pic\\Player%d.bmp",TextureID);
	D3DXCreateTextureFromFileEx(DXPlayerView::pDevice,			// Device
								File,
								20,								// Width
								30,								// Height
								1,
								D3DPOOL_DEFAULT,
								D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(1.0f,0.0f,1.0f,1.0f),		// pink = transparent
								&d3dxImageInfo,
								NULL,
								&pTexture);

    pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

void DXPlayerView::Draw(int X,int Y)
{
	if(pTexture == NULL || pSprite == NULL)
		return;
	D3DXVECTOR3 v(X,Y,0);
	pSprite->Draw(pTexture,NULL,NULL,&v,0xFFFFFFFF);
}

