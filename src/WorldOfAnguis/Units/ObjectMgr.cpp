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
	
	delete sHud;
	delete sWorld;
}

void ObjectMgr::Update()
{
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		if((*it)->IsActive())
			(*it)->Update();			// Paramters: WorldPointer <-> Terran Hittest | UnitsPointer <-> Unit Hittest //
		else
			{
			sDrawMgr->UnRegisterUnit(*it);
			delete *it;
			}
		}
}

void ObjectMgr::AddPlayer()
{
	Unit* unit = new Player(30,70);
	Objects.push_back(unit);
	sDrawMgr->RegisterUnit(unit,"..\\..\\pic\\Player\\Player1.bmp");
}

void ObjectMgr::CreateWorld()
{
	sWorld->LoadMaps("..\\..\\pic\\Map\\Map1");
}
