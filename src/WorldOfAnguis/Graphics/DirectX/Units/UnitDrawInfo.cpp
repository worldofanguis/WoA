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

UnitDrawInfo::UnitDrawInfo()
{
}

UnitDrawInfo::~UnitDrawInfo()
{
	UnloadTextures();
}

bool UnitDrawInfo::PreloadTextures(LPDIRECT3DDEVICE9 pDevice)
{
	TextureMap.clear();
	STextureInfo* TInfo;

	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Player\\Player1.bmp")) != NULL)		TextureMap["Player_1"] = TInfo; else return false;
	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Bullet\\Explosion.bmp")) != NULL)		TextureMap["Explosion"] = TInfo; else return false;
	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Bullet\\Def.bmp")) != NULL)			TextureMap["Bullet_Def"] = TInfo; else return false;
	if((TInfo = LoadTexture(pDevice,"..\\..\\pic\\Weapon\\Crosshair.bmp")) != NULL)		TextureMap["Crosshair"] = TInfo; else return false;

return true;
}

void UnitDrawInfo::UnloadTextures()
{
	for(std::map<const char*,UnitDrawInfo::STextureInfo*>::iterator it=TextureMap.begin();it!=TextureMap.end();it++)
		{
		SAFE_RELEASE(it->second->pTexture);
		delete it->second;
		}
	TextureMap.clear();
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

	/* Loadin the info file which contains additional informations about the unit texture (used for animations only) */
	char InfoFile[MAX_PATH];
	sprintf_s(InfoFile,sizeof(InfoFile),"%s.info.txt",FileName);
	fopen_s(&FKez,InfoFile,"r");

	if(FKez == NULL)
		{
		TInfo->AnimationLastFrame = 0;
		TInfo->AnimationSpeed = 0;
		}
	else
		{
		fscanf_s(FKez,"FrameCount: %d\n",&TInfo->AnimationLastFrame,sizeof(TInfo->AnimationLastFrame));
		fscanf_s(FKez,"AnimationSpeed: %d\n",&TInfo->AnimationSpeed,sizeof(TInfo->AnimationSpeed));
		fclose(FKez);
		}

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

UnitDrawInfo::STextureInfo* UnitDrawInfo::GetTextureInfo(char* TextureName)
{
	for(std::map<const char*,UnitDrawInfo::STextureInfo*>::iterator it=TextureMap.begin();it!=TextureMap.end();it++)
		{
		if(strcmp(it->first,TextureName) == NULL)
			return it->second;
		}

return NULL;
}

UnitDrawInfo::UnitInfo::UnitInfo(char* TextureName,FLAGS Flag)
{
	this->Flag = Flag;
	AnimationCurrentFrame = -1;
	AnimationFrameLastUpdateTime = 0;

	if(Flag == INVISIBLE)
		{
		TextureInfo = NULL;
		return;
		}

	TextureInfo = sUnitDrawInfo->GetTextureInfo(TextureName);
}
