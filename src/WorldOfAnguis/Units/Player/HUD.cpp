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


#include "HUD.h"
#include "Graphics/DirectX/DirectXInterface.h"

HUD::HUD()
{
	DXHUDView::LoadTexture();		// could be moved to the dxhudview class //
	DirectXInterface::RegisterHUD(this);
}

HUD::~HUD()
{
}
