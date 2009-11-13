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
 
#include "UnitDrawInfo.h"

UnitDrawInfo::UnitDrawInfo(LPDIRECT3DDEVICE9 pDevice,char* TextureFileName)
{
	AnimationFrame = 0;
	pTexture = NULL;
	if(!LoadTexture(pDevice,TextureFileName))
		throw "o.O";
}

UnitDrawInfo::~UnitDrawInfo()
{
	SAFE_RELEASE(pTexture);
}

bool UnitDrawInfo::LoadTexture(LPDIRECT3DDEVICE9 pDevice,char* FileName)
{
	FILE* FKez;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	fopen_s(&FKez,FileName,"rb");
	fread(&bmfh,sizeof(BITMAPFILEHEADER),1,FKez);
	if(bmfh.bfType != 0x4D42)		// check if its a BMP (BM flag) //
		{
		fclose(FKez);
		return false;
		}

	fread(&bmih,sizeof(BITMAPINFOHEADER),1,FKez);
	fclose(FKez);

	Width = bmih.biWidth;
	Height = bmih.biHeight;

	D3DXCreateTextureFromFileEx(pDevice,						// Device
								FileName,
								bmih.biWidth,					// Width
								bmih.biHeight,					// Height
								1,
								0,
								D3DFMT_A8R8G8B8,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								D3DCOLOR_XRGB(255,0,255),		// pink = transparent
								NULL,
								NULL,
								&pTexture);
return true;
}
