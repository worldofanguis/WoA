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

std::map<const char*,UnitDrawInfo::STextureInfo*> UnitDrawInfo::Textures;		// Static initialization o.O //

UnitDrawInfo::UnitDrawInfo(char* TextureName,FLAGS Flag)
{
	this->Flag = Flag;
	AnimationCurrentFrame = -1;

	if(Flag == INVISIBLE)
		{
		TextureInfo = NULL;
		return;
		}

	for(std::map<const char*,UnitDrawInfo::STextureInfo*>::iterator it=Textures.begin();it!=Textures.end();it++)
		{
		if(strcmp(it->first,TextureName) == NULL)
			{
			TextureInfo = it->second;
			return;
			}
		}
	throw "CantFindTheTexture";
}

UnitDrawInfo::~UnitDrawInfo()
{
}

bool UnitDrawInfo::PreloadTextures(LPDIRECT3DDEVICE9 pDevice)
{
	Textures.clear();
	STextureInfo* TInfo;

	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Player\\Player1.bmp")) != NULL)		Textures["Player_1"] = TInfo; else return false;
//	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Bullet\\Explosion.bmp")) != NULL)		Textures["Explosion"] = TInfo; else return false;
//	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Bullet\\Def.bmp")) != NULL)			Textures["Bullet_Def"] = TInfo; else return false;
	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Weapon\\Crosshair.bmp")) != NULL)		Textures["Crosshair"] = TInfo; else return false;

return true;
}

void UnitDrawInfo::UnloadTextures()
{
	for(std::map<const char*,UnitDrawInfo::STextureInfo*>::iterator it=Textures.begin();it!=Textures.end();it++)
		{
		SAFE_RELEASE(it->second->pTexture);
		delete it->second;
		}
	Textures.clear();
}

UnitDrawInfo::STextureInfo* UnitDrawInfo::LoadTexture(LPDIRECT3DDEVICE9 pDevice,char* FileName)
{
	FILE* FKez;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	fopen_s(&FKez,FileName,"rb");
	fread(&bmfh,sizeof(BITMAPFILEHEADER),1,FKez);
	if(bmfh.bfType != 0x4D42)		// check if its a BMP (BM flag) //
		{
		fclose(FKez);
		return NULL;
		}

	fread(&bmih,sizeof(BITMAPINFOHEADER),1,FKez);
	fclose(FKez);
	
	STextureInfo *TInfo = new STextureInfo;
	TInfo->Width = bmih.biWidth;
	TInfo->Height = bmih.biHeight;
	
	/* This must be read from a file */
	TInfo->AnimationLastFrame = 20;
	TInfo->AnimationSpeed = 25;		// Framechange delay //

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
								&(TInfo->pTexture));

return TInfo;
}
