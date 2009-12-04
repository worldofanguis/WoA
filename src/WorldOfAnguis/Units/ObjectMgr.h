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
#include "Unit.h"
#include "Units/Player/HUD.h"
#include "Graphics/DirectX/DrawMgr.h"
#include "World/World.h"


class ObjectMgr : public Singleton<ObjectMgr>
{
public:
	ObjectMgr();
	~ObjectMgr();
	
	void RegisterUnit(Unit* unit);
	void AddPlayer(int X,int Y,int TextureNumber);
	void CreateWorld();
	
	Unit* Me() {return Objects.front();}

	void Update();
private:
	std::vector<Unit*> Objects;
	std::vector<Unit*>::iterator it;
	std::vector<Unit*>::iterator itc;
};

#define sObjMgr ObjectMgr::Instance()