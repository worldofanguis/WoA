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


/* Class: UnitDrawInfo
 * Description: This class holds the drawing infos for each unit in the DrawMgr
 *				these infos are: Texture and current AnimationFrame
 *
 * Functions: Constructor
 *				creates the infoclass
 */


#pragma once
#include "Common.h"

class UnitDrawInfo
{
	friend class DrawMgr;		// to access private elements //
public:
	UnitDrawInfo(LPDIRECT3DDEVICE9 pDevice,char* FileName);
	~UnitDrawInfo();
	
private:
	bool LoadTexture(LPDIRECT3DDEVICE9 pDevice,char* FileName);

	int Width;
	int Height;
	LPDIRECT3DTEXTURE9 pTexture;
	int AnimationFrame;
};
