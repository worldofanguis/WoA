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

LPDIRECT3DDEVICE9 DXPlayerView::pDevice = NULL;
LPDIRECT3DTEXTURE9 DXPlayerView::pTexture = NULL;
LPD3DXSPRITE DXPlayerView::pSprite = NULL;

DXPlayerView::DXPlayerView()
{
}

DXPlayerView::~DXPlayerView()
{
}

void DXPlayerView::LoadTexture()
{
	D3DXIMAGE_INFO d3dxImageInfo;
	D3DXCreateTextureFromFileEx(DXPlayerView::pDevice,			// Device
								"..\\..\\pic\\Player.bmp",
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
								&DXPlayerView::pTexture);

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

