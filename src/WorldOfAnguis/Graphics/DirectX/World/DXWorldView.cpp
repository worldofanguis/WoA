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
 

#include "DXWorldView.h"

LPDIRECT3DDEVICE9 DXWorldView::pDevice = NULL;
LPD3DXSPRITE DXWorldView::pSprite = NULL;

DXWorldView::DXWorldView()
{
}

DXWorldView::~DXWorldView()
{
	SAFE_RELEASE(pDisplaySurface);
	SAFE_RELEASE(pWorkSurface);
	SAFE_RELEASE(pOriginalSurface);
}

void DXWorldView::Draw(int Left,int Top,int Width,int Height)
{
	if(pDisplaySurface == NULL || pSprite == NULL)
		return;
	RECT r = {Left,Top,Left+Width,Top+Height};
	/* Copy the r region from pDisplaySurface to the screen */
	pSprite->Draw(pDisplaySurface,&r,NULL,NULL,0xFFFFFFFF);
}

void DXWorldView::UpdateSurface(char *Map,int MapWidth,int PPHM)
{
	D3DLOCKED_RECT SurfaceRect;
	D3DLOCKED_RECT OriginalRect;
	
	pWorkSurface->LockRect(0,&SurfaceRect,NULL,0);			// Lock the surfaces for manipulation //
	pOriginalSurface->LockRect(0,&OriginalRect,NULL,D3DLOCK_READONLY);
	
	BYTE* Dest = (BYTE*)SurfaceRect.pBits;				// Get the pointer to the surface //
	BYTE* Source = (BYTE*)OriginalRect.pBits;			// We want a byte - byte copy //
		
	for(int h=0;h<SurfaceHeight;h++)
		{
		for(int w=0;w<SurfaceWidth;w++)
			{
			if(Map[(((int)(h/PPHM))*MapWidth)+((int)(w/PPHM))])		// There is something on the map there //
				{
				*(DWORD*)Dest = *(DWORD*)Source;				// Copy 1 pixel from the source to the destination //
				}
			Dest+=4;				// Move the pointer with 4 bytes (1 pixel (XRGB))
			Source+=4;
			}
		}
	pDisplaySurface->UnlockRect(0);					// Unlock the surfaces //
	pOriginalSurface->UnlockRect(0);

	pDevice->UpdateTexture(pWorkSurface,pDisplaySurface);
}

bool DXWorldView::LoadWorldTexture(char *File)
{
	FILE *FKez;
	fopen_s(&FKez,File,"rb");
	if(FKez == NULL)
		return false;

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	fread(&bmfh,sizeof(BITMAPFILEHEADER),1,FKez);
	if(bmfh.bfType != 0x4D42)		// check if its a BMP (BM flag) //
		{
		fclose(FKez);
		return false;
		}

	fread(&bmih,sizeof(BITMAPINFOHEADER),1,FKez);
	fclose(FKez);
	
	BytesPerPixel = bmih.biBitCount/8;
	SurfaceWidth = bmih.biWidth;
	SurfaceHeight = bmih.biHeight;

	D3DXCreateTextureFromFileEx(DXWorldView::pDevice,			// Device
								File,
								SurfaceWidth,					// Width
								SurfaceHeight,					// Height
								1,
								0,
								D3DFMT_UNKNOWN,
								D3DPOOL_SYSTEMMEM,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(1.0f,0.0f,1.0f,1.0f),		// pink = transparent
								NULL,
								NULL,
								&pOriginalSurface);

	pDevice->CreateTexture(SurfaceWidth,SurfaceHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&pWorkSurface,NULL);
	pDevice->CreateTexture(SurfaceWidth,SurfaceHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&pDisplaySurface,NULL);
	
//	pDevice->UpdateTexture(pOriginalSurface,pDisplaySurface);
return true;
}
