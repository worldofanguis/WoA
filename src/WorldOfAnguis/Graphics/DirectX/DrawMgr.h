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


/* Class: DrawMgr
 * Description: This class holds all the drawing infos for our objects (players, bullets, pickups, etc)
 *
 * Functions: Setup(...)
 *				setup the class with the drawing devices
 *			  RegisterUnit(...)
 *				this function is called if we created an unit which needs drawing
 *			  UnregisterUnit(...)
 *				if the drawing is no longer needed (the unit is destroyed)
 *			  Draw(...)
 *				the function that draws all InSight object on the screen buffer
 */

		
#pragma once
#include "Common.h"
#include "Singleton.h"
#include "Units/Unit.h"
#include "Units/Weapon/Bullet.h"
#include "Units/Player/Player.h"
#include "Units/Explosion/Explosion.h"
#include "Units/UnitDrawInfo.h"

typedef std::pair<Unit*,UnitDrawInfo*> UnitInfo;
class DrawMgr : public Singleton<DrawMgr>
{
public:
	DrawMgr();
	~DrawMgr();
	
	void Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite,int Width,int Height);
	
	void RegisterUnit(Unit* unit,char* TextureFileName,UnitDrawInfo::FLAGS Flag);
	void UnRegisterUnit(Unit* unit);
	
	void Draw(int ViewLeft,int ViewTop);
	

private:
	bool InSight(Unit* unit,int ViewLeft,int ViewTop);

	void DrawPlayer(Player* player,UnitDrawInfo* unitinfo,int ViewLeft,int ViewTop);
	void DrawBullet(Bullet* bullet,UnitDrawInfo* unitinfo,int ViewLeft,int ViewTop);
	void DrawExplosion(Explosion* explosion,UnitDrawInfo* unitinfo,int ViewLeft,int ViewTop);

	std::vector<UnitInfo> Objects;
	std::vector<UnitInfo>::iterator it;
	
	int ViewWidth;
	int ViewHeight;
	
	DWORD CurrentTime;
	
	UnitDrawInfo* Crosshair;
	
	LPD3DXSPRITE pSprite;
	LPDIRECT3DDEVICE9 pDevice;
};

#define sDrawMgr DrawMgr::Instance()