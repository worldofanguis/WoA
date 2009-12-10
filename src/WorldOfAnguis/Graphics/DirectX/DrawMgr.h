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
#include "Units/Weapon/Bullet.h"
#include "Units/Player/Player.h"
#include "Units/UnitDrawInfo.h"

typedef std::pair<Unit*,UnitDrawInfo*> UnitInfo;
class DrawMgr : public Singleton<DrawMgr>
{
public:
	DrawMgr();
	~DrawMgr();
	
	void Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite,int Width,int Height);
	
	void RegisterUnit(Unit* unit,char* TextureFileName);
	void UnRegisterUnit(Unit* unit);
	
	void Draw(int ViewLeft,int ViewTop);
	
	void DrawPlayer(Player* player,UnitDrawInfo* unitinfo,int ViewLeft,int ViewTop);
	void DrawBullet(Bullet* bullet,UnitDrawInfo* unitinfo,int ViewLeft,int ViewTop);

private:
	bool InSight(Unit* unit,int ViewLeft,int ViewTop);

	std::vector<UnitInfo> Objects;
	std::vector<UnitInfo>::iterator it;
	
	int ViewWidth;
	int ViewHeight;
	
	UnitDrawInfo* Crosshair;
	
	LPD3DXSPRITE pSprite;
	LPDIRECT3DDEVICE9 pDevice;
};

#define sDrawMgr DrawMgr::Instance()