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
#include "Graphics/DirectX/Units/DrawMgr.h"

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
	ObjectMgr();
	~ObjectMgr();
	
	void AddPlayer();

	void Update();
private:
	std::vector<Unit*> Objects;
	std::vector<Unit*>::iterator it;
};

#define ObjMgr ObjectMgr::Instance()