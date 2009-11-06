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

Player::Player(int X,int Y)
{
	this->X = X;
	this->Y = Y;
	Width = 20;
	Height = 30;
	Life = 100;
	
	DirectXInterface::RegisterUnit(this);
}

Player::~Player()
{
	DirectXInterface::UnRegisterUnit(this);
}
