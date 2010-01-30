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
#include "Time.h"

DrawMgr::DrawMgr()
{
	Objects.clear();
	ViewWidth = 0;
	ViewHeight = 0;
	
	Crosshair = NULL;
}

DrawMgr::~DrawMgr()
{
	for(it=Objects.begin();it!=Objects.end();it++)
		delete it->second;

	Objects.clear();

	delete Crosshair;
	delete sUnitDrawInfo;
}

void DrawMgr::Setup(LPDIRECT3DDEVICE9 pDevice,LPD3DXSPRITE pSprite,int Width,int Height)
{
	this->pSprite = pSprite;
	ViewWidth = Width;
	ViewHeight = Height;
	
	if(!sUnitDrawInfo->PreloadTextures(pDevice))
		throw "Phail!";
	
	Crosshair = new UnitDrawInfo::UnitInfo("Crosshair",UnitDrawInfo::REMOVE_NEVER);
}

void DrawMgr::RegisterUnit(Unit* unit,char* TextureName,UnitDrawInfo::FLAGS Flag)
{
	Objects.push_back(UnitInfo(unit,new UnitDrawInfo::UnitInfo(TextureName,Flag)));
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
	CurrentTime = GetMSTime();
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		if(it->second->Flag == UnitDrawInfo::INVISIBLE)
			continue;		// Invisible objects are ignored //

		if(GetMSTimeDiff(it->second->AnimationFrameLastUpdateTime,CurrentTime) > it->second->TextureInfo->AnimationSpeed)
			{		// Time to change the animation frame //
			it->second->AnimationFrameLastUpdateTime = CurrentTime;
			if(++(it->second->AnimationCurrentFrame) == it->second->TextureInfo->AnimationLastFrame)
				{	// Reached the last animation frame, remove the object, or start again //
				if(it->second->Flag == UnitDrawInfo::REMOVE_AT_LAST_FRAME)
					it->first->SetState(Unit::STATE_INACTIVE);
				else
					it->second->AnimationCurrentFrame = 0;
				}
			}
		if(InSight(it->first,ViewLeft,ViewTop))
			{
			switch(it->first->GetType())
				{
				case Unit::PLAYER:
					DrawPlayer(reinterpret_cast<Player*>(it->first),it->second,ViewLeft,ViewTop);
					break;
				case Unit::BULLET:
					DrawBullet(reinterpret_cast<Bullet*>(it->first),it->second,ViewLeft,ViewTop);
					break;
				case Unit::EXPLOSION:
					DrawExplosion(reinterpret_cast<Explosion*>(it->first),it->second,ViewLeft,ViewTop);
					break;
				}
			}
		}
}

void DrawMgr::DrawPlayer(Player* player,UnitDrawInfo::UnitInfo* unitinfo,int ViewLeft,int ViewTop)
{
	D3DXVECTOR3 v(player->GetX()-ViewLeft,player->GetY()-ViewTop,0);
	pSprite->Draw(unitinfo->TextureInfo->pTexture,NULL,NULL,&v,0xFFFFFFFF);
	
	v.x = player->GetX()-ViewLeft+player->GetWidth()/2+cos(player->GetAngle())*50;
	v.y = player->GetY()-ViewTop+player->GetHeight()/2-sin(player->GetAngle())*50;
	pSprite->Draw(Crosshair->TextureInfo->pTexture,NULL,NULL,&v,0xFFFFFFFF);
}

void DrawMgr::DrawBullet(Bullet* bullet,UnitDrawInfo::UnitInfo* unitinfo,int ViewLeft,int ViewTop)
{
	D3DXVECTOR3 v(bullet->GetX()-ViewLeft,bullet->GetY()-ViewTop,0);
	pSprite->Draw(unitinfo->TextureInfo->pTexture,NULL,NULL,&v,0xFFFFFFFF);
}

void DrawMgr::DrawExplosion(Explosion* explosion,UnitDrawInfo::UnitInfo* unitinfo,int ViewLeft,int ViewTop)
{
	D3DXVECTOR3 v(explosion->GetX()-ViewLeft-10,explosion->GetY()-ViewTop-10,0);	// -10 is because the explosion animation is bigger than the real explosion
	RECT SrcRect = {unitinfo->AnimationCurrentFrame*(explosion->GetWidth()+20),0,unitinfo->AnimationCurrentFrame*(explosion->GetWidth()+20)+(explosion->GetWidth()+20),explosion->GetHeight()+20};
	pSprite->Draw(unitinfo->TextureInfo->pTexture,&SrcRect,NULL,&v,0xFFFFFFFF);
}
