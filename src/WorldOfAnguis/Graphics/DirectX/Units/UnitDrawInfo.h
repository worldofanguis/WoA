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
 
#pragma once
#include "Common.h"

class UnitDrawInfo
{
public:
	UnitDrawInfo(LPDIRECT3DDEVICE9 pDevice,char* FileName);
	~UnitDrawInfo();
	bool LoadTexture(LPDIRECT3DDEVICE9 pDevice,char* FileName);
	
	LPDIRECT3DTEXTURE9 GetTexture() {return pTexture;}
	int GetWidth() {return Width;}
	int GetHeight() {return Height;}
	
	int AnimationFrame;
private:
	int Width;
	int Height;
	LPDIRECT3DTEXTURE9 pTexture;
};
