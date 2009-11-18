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

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
	ObjectMgr();
	~ObjectMgr();
	
	void AddPlayer();
	void CreateWorld();
	
	Unit* Me() {return Objects.front();}

	void Update();
private:
	std::vector<Unit*> Objects;
	std::vector<Unit*>::iterator it;
};

#define sObjMgr ObjectMgr::Instance()