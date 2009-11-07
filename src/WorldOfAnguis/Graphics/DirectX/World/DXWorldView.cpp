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
LPDIRECT3DSURFACE9 DXWorldView::pBackBuffer = NULL;

DXWorldView::DXWorldView()
{
}

DXWorldView::~DXWorldView()
{
	SAFE_RELEASE(pSurface);
	SAFE_RELEASE(pOriginalSurface);
}

void DXWorldView::Draw(int Left,int Top,int Width,int Height)
{
	if(pSurface == NULL || pBackBuffer == NULL)
		return;
	RECT r = {Left,Top,Left+Width,Top+Height};
	/* Copy the r region from pSurface to the whole pBackBuffer */
	pDevice->UpdateSurface(pSurface,&r,pBackBuffer,NULL);
}

void DXWorldView::UpdateSurface(char *Map,int MapWidth,int PPHM)
{
	D3DLOCKED_RECT SurfaceRect;
	D3DLOCKED_RECT OriginalRect;
	
	pSurface->LockRect(&SurfaceRect,NULL,0);			// Lock the surfaces for manipulation //
	pOriginalSurface->LockRect(&OriginalRect,NULL,D3DLOCK_READONLY);
	
	BYTE* Dest = (BYTE*)SurfaceRect.pBits;				// Get the pointer to the surface //
	BYTE* Source = (BYTE*)OriginalRect.pBits;			// We want a byte - byte copy //
		
	for(int h=0;h<SurfaceHeight;h++)
		{
		for(int w=0;w<SurfaceWidth;w++)
			{
			if(Map[(((int)(h/PPHM))*MapWidth)+((int)(w/PPHM))])		// There is something on the map there //
				{
				memcpy(Dest,Source,BytesPerPixel);				// Copy 1 Pixel //
				//*(DWORD*)Dest = *(DWORD*)Source;				// This line does the same //
				}
			Dest+=4;				// Move the pointer with 4 bytes (1 pixel (XRGB))
			Source+=4;
			}
		}
	pSurface->UnlockRect();					// Unlock the surfaces //
	pOriginalSurface->UnlockRect();
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

	pDevice->CreateOffscreenPlainSurface(SurfaceWidth,SurfaceHeight,D3DFMT_X8R8G8B8,D3DPOOL_SYSTEMMEM,&pSurface,NULL);
	pDevice->CreateOffscreenPlainSurface(SurfaceWidth,SurfaceHeight,D3DFMT_X8R8G8B8,D3DPOOL_SYSTEMMEM,&pOriginalSurface,NULL);
	D3DXLoadSurfaceFromFile(pOriginalSurface,NULL,NULL,File,NULL,D3DX_FILTER_LINEAR,D3DCOLOR_ARGB(255,255,0,255),NULL);
	/* This call is requied because of some conversions (not sure, but this way its working ^^) */
//	D3DXLoadSurfaceFromSurface(pSurface,NULL,NULL,pOriginalSurface,NULL,NULL,D3DX_FILTER_LINEAR,0);		// Copy the original textured map to the display buffer //
return true;
}
