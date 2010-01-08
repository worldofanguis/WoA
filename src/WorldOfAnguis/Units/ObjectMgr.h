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
#include "Units/Player/Player.h"
#include "Units/Weapon/Bullet.h"
#include "Units/Player/HUD.h"
#include "Graphics/DirectX/DrawMgr.h"
#include "World/World.h"


class ObjectMgr : public Singleton<ObjectMgr>
{
public:
	ObjectMgr();
	~ObjectMgr();

	Player* Me();

	void RegisterUnit(Unit* unit);

	void CreateWorld();

	void Update();
private:
	std::vector<Unit*> Objects;
	std::vector<Unit*> ToPushBack;
	
	std::vector<Unit*>::iterator it;
	std::vector<Unit*>::iterator itc;
	
	bool Iteration;
};

#define sObjMgr ObjectMgr::Instance()