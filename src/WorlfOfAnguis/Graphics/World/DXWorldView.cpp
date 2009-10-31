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
 

#include "DXWorldView.h"

LPDIRECT3DDEVICE9 DXWorldView::pDevice = NULL;
LPDIRECT3DSURFACE9 DXWorldView::pSurface = NULL;

DXWorldView::DXWorldView()
{
}

DXWorldView::~DXWorldView()
{
}

void DXWorldView::Draw(int Left,int Top,int Width,int Height)
{
}
