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

Player::Player()
{
	Width = 20;
	Height = 30;
	DirectXInterface::RegisterUnit(this);
}

Player::Player(int X,int Y)
{
	this->X = X;
	this->Y = Y;
	Width = 20;
	Height = 30;
}

Player::~Player()
{
	DirectXInterface::UnRegisterUnit(this);
}

void Player::Update()
{
	Sleep(10);
}