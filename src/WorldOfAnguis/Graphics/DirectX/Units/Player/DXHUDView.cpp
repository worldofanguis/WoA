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


#include "DXHUDView.h"

LPDIRECT3DDEVICE9 DXHUDView::pDevice = NULL;
LPD3DXSPRITE DXHUDView::pSprite = NULL;

DXHUDView::DXHUDView()
{
}

DXHUDView::~DXHUDView()
{
}

void DXHUDView::Draw(int Health,int WeaponID)
{
	if(pSprite == NULL)
		return;
}

