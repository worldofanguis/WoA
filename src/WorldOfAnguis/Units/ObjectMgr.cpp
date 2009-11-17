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
 
#include "ObjectMgr.h"

ObjectMgr::ObjectMgr()
{
	Objects.clear();
}

ObjectMgr::~ObjectMgr()
{
	for(it=Objects.begin();it!=Objects.end();it++)
		delete *it;
	
	Objects.clear();
}

void ObjectMgr::Update()
{
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		if((*it)->IsActive())
			(*it)->Update();			// Paramters: WorldPointer <-> Terran Hittest | UnitsPointer <-> Unit Hittest //
		else
			{
			DrwMgr->UnRegisterUnit(*it);
			delete *it;
			}
		}
}

void ObjectMgr::AddPlayer()
{
	Unit* unit = new Player(20,30);
	Objects.push_back(unit);
	DrwMgr->RegisterUnit(unit,"..\\..\\pic\\Player\\Player1.bmp");
}
