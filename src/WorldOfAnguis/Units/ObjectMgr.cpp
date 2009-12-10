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
	ToPushBack.clear();
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
			if((*it)->GetType() == Unit::EXPLOSION)
				{
				sWorld->Explode(*it);
				for(itc=Objects.begin();itc!=Objects.end();itc++)
					if((*itc)->GetType() == Unit::PLAYER && (*itc)->IsActive())
						(*itc)->Explode(*it);

				(*it)->Deactivate();
				}
			else
				{
				(*it)->CollisionWorld();
				
				//for(itc=Objects.begin();itc!=Objects.end();itc++)
				//	{
				//	if((*itc)->IsActive())
				//		(*it)->CollisionUnit(*itc);
				//	}
				(*it)->Update();
				}
			}
		else
			{
			sDrawMgr->UnRegisterUnit(*it);
			delete *it;
			it = Objects.erase(it);
			if(it == Objects.end())
				break;
			}
		}
		
	if(!ToPushBack.empty())
		{
		for(std::vector<Unit*>::iterator itp=ToPushBack.begin();itp!=ToPushBack.end();itp++)
			Objects.push_back(*itp);
		
		ToPushBack.clear();
		}
}

void ObjectMgr::RegisterUnit(Unit* unit)
{
	ToPushBack.push_back(unit);
}

void ObjectMgr::CreateWorld()
{
	sWorld->LoadMaps("..\\..\\pic\\Map\\Map1");
}
