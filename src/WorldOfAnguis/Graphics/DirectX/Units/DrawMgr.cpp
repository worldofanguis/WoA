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
 

#include "DrawMgr.h"

DrawMgr::DrawMgr(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite)
{
	this->pDevice = pDevice;
	this->pSprite = pSprite;
	Objects.clear();
}

DrawMgr::~DrawMgr()
{
	for(it=Objects.begin();it!=Objects.end();it++)
		delete it->second;
	
	Objects.clear();
}

void DrawMgr::RegisterUnit(Unit* unit,char* TextureFileName)
{
	Objects.push_back(UnitInfo(unit,new UnitDrawInfo(pDevice,TextureFileName)));
}

void DrawMgr::UnRegisterUnit(Unit* unit)
{
	for(it=Objects.begin();it!=Objects.end();it++)
		if(it->first == unit)
			{
			delete it->second;
			Objects.erase(it);
			break;
			}
}

bool DrawMgr::InSight(Unit* unit,int ViewLeft,int ViewTop)
{
	/* Check if the object we want to draw is truly in sight (if not just leave it alone) */
	if((ViewLeft < (unit->GetX()+unit->GetWidth())) && (ViewTop < (unit->GetY()+unit->GetHeight())) &&
	   ((ViewLeft+ViewWidth) > unit->GetX()) && ((ViewTop+ViewHeight) > unit->GetY()))
		return true;
return false;
}

void DrawMgr::Draw(int ViewLeft,int ViewTop)
{
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		if(InSight(it->first,ViewLeft,ViewTop))
			{
			switch(it->first->GetType())
				{
				case Unit::PLAYER:
					DrawPlayer(reinterpret_cast<Player*>(it->first),it->second);
					break;
				}
			}
		}
}

void DrawMgr::DrawPlayer(Player* player,UnitDrawInfo* unitinfo)
{
	D3DXVECTOR3 v(player->GetX(),player->GetY(),0);
	pSprite->Draw(unitinfo->GetTexture(),NULL,NULL,&v,0xFFFFFFFF);
}
