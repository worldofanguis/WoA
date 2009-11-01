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
}

void DXWorldView::Draw(int Left,int Top,int Width,int Height)
{
	RECT r = {Left,Top,Left+Width,Top+Height};
	/* Copy the r region from pSurface to the whole pBackBuffer */
	pDevice->UpdateSurface(pSurface,&r,pBackBuffer,NULL);
}

void DXWorldView::UpdateSurface(char *Map)
{
	// Create pSurface from the Map and the pOriginalSurface //
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
	if(bmfh.bfType != 0x4D42)		// BM //
		{
		fclose(FKez);
		return false;
		}
	fread(&bmih,sizeof(BITMAPINFOHEADER),1,FKez);
	fclose(FKez);
	
	SurfaceWidth = bmih.biWidth;
	SurfaceHeight = bmih.biHeight;

	pDevice->CreateOffscreenPlainSurface(SurfaceWidth,SurfaceHeight,D3DFMT_X8R8G8B8,D3DPOOL_SYSTEMMEM,&pSurface,NULL);
	pDevice->CreateOffscreenPlainSurface(SurfaceWidth,SurfaceHeight,D3DFMT_X8R8G8B8,D3DPOOL_SYSTEMMEM,&pOriginalSurface,NULL);
	D3DXLoadSurfaceFromFile(pOriginalSurface,NULL,NULL,File,NULL,D3DX_FILTER_LINEAR,D3DCOLOR_ARGB(255,0,0,0),NULL);
	D3DXLoadSurfaceFromSurface(pSurface,NULL,NULL,pOriginalSurface,NULL,NULL,D3DX_FILTER_LINEAR,0);

return true;
}
