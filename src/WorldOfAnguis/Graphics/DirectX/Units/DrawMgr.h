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
#include "Singleton.h"
#include "Units/Unit.h"
#include "Units/Player/Player.h"
#include "UnitDrawInfo.h"

typedef std::pair<Unit*,UnitDrawInfo*> UnitInfo;
class DrawMgr : public Singleton<DrawMgr>
{
public:
	DrawMgr();
	~DrawMgr();
	
	void Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite) {this->pDevice = pDevice; this->pSprite=pSprite;}
	void SetScreenSize(int Width,int Height) {ViewWidth = Width; ViewHeight = Height;}
	
	void RegisterUnit(Unit* unit,char* TextureFileName);
	void UnRegisterUnit(Unit* unit);
	
	void Draw(int ViewLeft,int ViewTop);
	
	void DrawPlayer(Player* player,UnitDrawInfo* unitinfo);
private:
	bool InSight(Unit* unit,int ViewLeft,int ViewTop);

	std::vector<UnitInfo> Objects;
	std::vector<UnitInfo>::iterator it;
	
	int ViewWidth;
	int ViewHeight;
	
	LPD3DXSPRITE pSprite;
	LPDIRECT3DDEVICE9 pDevice;
};

#define DrwMgr DrawMgr::Instance()