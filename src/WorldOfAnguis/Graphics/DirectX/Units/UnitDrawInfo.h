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
#include "Singleton.h"



class UnitDrawInfo : public Singleton<UnitDrawInfo>
{
/* Predefinitions */
private: struct STextureInfo;

public:
	enum FLAGS {REMOVE_NEVER,			// REMOVE_NEVER: this object can only be removed by setting the Unit->State to STATE_INACTIVE
				REMOVE_AT_LAST_FRAME,	// REMOVE_AT_LAST_FRAME: if this flag is set, the object will be removed if the animation reaches its end. Good for STATE_GRAPHICS_ONLY units [for now its used for the delayed remove of the explosions]
				INVISIBLE				// INVISIBLE: the object will be ignored in the DrawMgr. [used for digging]
			   };

	class UnitInfo
	{
	public:
		UnitInfo(char* TextureName,FLAGS Flag);
		STextureInfo *TextureInfo;

		DWORD AnimationFrameLastUpdateTime;
		int AnimationCurrentFrame;

		FLAGS Flag;
	};

	UnitDrawInfo();
	~UnitDrawInfo();

	bool PreloadTextures(LPDIRECT3DDEVICE9 pDevice);

private:
	struct STextureInfo
	{
		LPDIRECT3DTEXTURE9 pTexture;
		int Width;
		int Height;
		int AnimationSpeed;
		int AnimationLastFrame;
	};

	void UnloadTextures();
	STextureInfo* GetTextureInfo(char* TextureName);
	STextureInfo* LoadTexture(LPDIRECT3DDEVICE9 pDevice,char* FileName);
	std::map<const char*,UnitDrawInfo::STextureInfo*> TextureMap;
};

#define sUnitDrawInfo UnitDrawInfo::Instance()