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
		if((*it)->GetState() == Unit::STATE_ACTIVE)
			{
			if((*it)->GetType() == Unit::EXPLOSION)
				{
				sWorld->Explode(*it);
				for(itc=Objects.begin();itc!=Objects.end();itc++)
					if((*itc)->GetType() == Unit::PLAYER && (*itc)->GetState() == Unit::STATE_ACTIVE)
						(*itc)->Explode(*it);

				(*it)->SetState(Unit::STATE_GRAPHICS_ONLY);		// Graphics only units will be removed if the DrawMgr wants them removed //
				}
			else
				{
				(*it)->CollisionWorld();
/*
				if((*it)->GetType() == Unit::PLAYER)
					{
					for(itc=Objects.begin();itc!=Objects.end();itc++)
						{
						if((*itc)->IsActive())
							(*it)->CollisionUnit(*itc);
						}
					}
*/

				if((*it)->GetType() == Unit::BULLET)
					{
					for(itc=Objects.begin();itc!=Objects.end();itc++)
						{
						if((*itc)->GetState() == Unit::STATE_ACTIVE && (*itc)->GetType() != Unit::BULLET)
							(*it)->CollisionUnit(*itc);
						}
					}

				(*it)->Update();
				}
			}
		else if((*it)->GetState() == Unit::STATE_INACTIVE)
			{
			sDrawMgr->UnRegisterUnit(*it);
			delete *it;
			it = Objects.erase(it);
			if(it == Objects.end())
				break;
			}
		else if((*it)->GetState() == Unit::STATE_GRAPHICS_ONLY)
			{
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
	sWorld->LoadMap("..\\..\\pic\\Map\\Map1");
}

Player* ObjectMgr::Me()
{
	if(Objects.empty())
		return NULL;

return (Player*)Objects.front();
}
