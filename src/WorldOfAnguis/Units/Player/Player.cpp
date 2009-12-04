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


#include "Player.h"
#include "Graphics/DirectX/DirectXInterface.h"

Player::Player(int X,int Y,int SkinID) : Unit(X,Y,PLAYER)
{
	Width = 20;
	Height = 30;
	Life = 100;
	Angle = 0;
	Jumping = false;
	
	char PlayerTexture[MAX_PATH];
	sprintf_s(PlayerTexture,sizeof(PlayerTexture),"..\\..\\pic\\Player\\Player%d.bmp",SkinID);
	sDrawMgr->RegisterUnit((Unit*)this,PlayerTexture);
}

Player::~Player()
{

}
