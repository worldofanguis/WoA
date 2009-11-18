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
#include "Graphics/DirectX/HUD/DXHUDView.h"

class HUD : public Singleton<HUD>
{
public:
	HUD();
	~HUD();
	
	void Update(DXHUDView::HUD_PART Part,int Data) {sHudView->Update(Part,Data);}
private:

};

#define sHud HUD::Instance()