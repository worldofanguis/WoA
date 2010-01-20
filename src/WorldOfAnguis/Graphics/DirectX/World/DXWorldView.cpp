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

DXWorldView::DXWorldView()
{
	pDevice = NULL;
	pSprite = NULL;
	
	pDisplaySurface = NULL;		// Main texture surface | Locaton: video card memory //
	pWorkSurface = NULL;		// Surface used for creating the new masked landscape | Location: comp memory //
	pOriginalSurface = NULL;	// Surface used to hold the original landscape | Location: comp memory //
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

void DXWorldView::UpdateSurface(char *Map,int MapWidth,int PPHM,RECT* DirtyRegion)
{
	D3DLOCKED_RECT SurfaceRect;
	D3DLOCKED_RECT OriginalRect;
	
	RECT WholeSurface = {0,0,SurfaceWidth,SurfaceHeight};
	if(DirtyRegion == NULL)
		DirtyRegion = &WholeSurface;
	else
		{
		if(DirtyRegion->top  < 0) DirtyRegion->top  = 0;
		if(DirtyRegion->left < 0) DirtyRegion->left = 0;

		if(DirtyRegion->bottom > SurfaceHeight) DirtyRegion->bottom = SurfaceHeight;
		if(DirtyRegion->right  > SurfaceWidth)  DirtyRegion->right  = SurfaceWidth;
		}

	/* NOTE: We are working in the WorkSurface because we cant access directly the DisplaySurface */

	/* NOTE: If the DirtyRegion is specified in the LockRect parameter list
	 * the returned memory address will be the beginning of the dirtyregion
	 */
	pWorkSurface->LockRect(0,&SurfaceRect,DirtyRegion,0);			// Lock the surfaces for manipulation //
	pOriginalSurface->LockRect(0,&OriginalRect,DirtyRegion,D3DLOCK_READONLY);	// We use the same dirtyregion to avoid memory address conversion //

	BYTE* Dest = (BYTE*)SurfaceRect.pBits;				// Get the pointer to the surface memory //
	BYTE* Source = (BYTE*)OriginalRect.pBits;

	for(int h=0;h<DirtyRegion->bottom-DirtyRegion->top;h++)		// Copy height: bottom-top //
		{
		for(int w=0;w<DirtyRegion->right-DirtyRegion->left;w++)	// Copy width: right-left //
			{
			if(Map[(((int)((h+DirtyRegion->top)/PPHM))*MapWidth)+((int)((w+DirtyRegion->left)/PPHM))])		// There is something on the map there //
				*(DWORD*)Dest = *(DWORD*)Source;				// Copy 1 pixel from the source to the destination //
			else
				*(DWORD*)Dest =	0;

			Dest   +=4;				// Move the pointer with 4 bytes (1 pixel (ARGB))
			Source +=4;
			}
		Dest   += SurfaceRect.Pitch-(DirtyRegion->right*4) /*NextLine*/ + (DirtyRegion->left*4); /*DirtyRegionStart */
		Source += SurfaceRect.Pitch-(DirtyRegion->right*4) /*NextLine*/ + (DirtyRegion->left*4); /*DirtyRegionStart */
		}

	pWorkSurface->UnlockRect(0);					// Unlock the surfaces //
	pOriginalSurface->UnlockRect(0);

	/* Update the DisplaySurface */
	pDevice->UpdateTexture(pWorkSurface,pDisplaySurface);
}

bool DXWorldView::LoadWorldTexture(char *File)
{
	if(pDevice == NULL)
		return false;

	FILE *FKez;
	fopen_s(&FKez,File,"rb");
	if(FKez == NULL)
		return false;

	SAFE_RELEASE(pDisplaySurface);		// Destroy the previous stuffs if any //
	SAFE_RELEASE(pWorkSurface);
	SAFE_RELEASE(pOriginalSurface);

	BITMAPFILEHEADER bmfh;		 // Bitmap file headers //
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

	D3DXCreateTextureFromFileEx(pDevice,			// Device
								File,
								SurfaceWidth,					// Width
								SurfaceHeight,					// Height
								1,								// Levels
								0,								// Usage
								D3DFMT_A8R8G8B8,				// Format
								D3DPOOL_SYSTEMMEM,				// Memory pool
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_XRGB(255,0,255),		// pink = transparent
								NULL,
								NULL,
								&pOriginalSurface);

	/* NOTE: WorkSurface (texture) for generating the DisplaySurface from the Original and the HitMap
	 *       we do it this way because its in the system memory and the DisplaySurface is in the video memory and we dont want to (and cant) access to that
	 */
	pDevice->CreateTexture(SurfaceWidth,SurfaceHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&pWorkSurface,NULL);
	pDevice->CreateTexture(SurfaceWidth,SurfaceHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&pDisplaySurface,NULL);
	
//	pDevice->UpdateTexture(pOriginalSurface,pDisplaySurface);	// Used for testing //
return true;
}
