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
		{
		sDrawMgr->UnRegisterUnit(*it);
		delete *it;
		}
	
	Objects.clear();
	
	delete sHud;
	delete sWorld;
}

void ObjectMgr::Update()
{
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		if((*it)->IsActive())
			{
			(*it)->CollisionWorld();
			
			for(itc=Objects.begin();itc!=Objects.end();itc++)
				(*it)->CollisionUnit(*itc);
			
			(*it)->Update();
			}
		else
			{
			sDrawMgr->UnRegisterUnit(*it);
			delete *it;
			}
		}
}

void RegisterUnit(Unit* unit)
{

}

void ObjectMgr::AddPlayer(int X,int Y,int TextureNumber)
{
	Unit* unit = new Player(X,Y);
	Objects.push_back(unit);
	char PlayerTexture[MAX_PATH];
	sprintf_s(PlayerTexture,sizeof(PlayerTexture),"..\\..\\pic\\Player\\Player%d.bmp",TextureNumber);
	sDrawMgr->RegisterUnit(unit,PlayerTexture);
}

void ObjectMgr::CreateWorld()
{
	sWorld->LoadMaps("..\\..\\pic\\Map\\Map1");
}
