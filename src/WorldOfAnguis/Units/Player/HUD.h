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
#include "Graphics/DirectX/Units/Player/DXHUDView.h"

class HUD : DXHUDView
{
public:
	HUD();
	~HUD();
	
	void Draw() {DXHUDView::Draw();}
	void Update(DXHUDView::HUD_PART Part,int Data) {DXHUDView::Update(Part,Data);}
private:

};