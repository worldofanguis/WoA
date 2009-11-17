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

Player::Player(int X,int Y) : Unit(PLAYER)
{
	this->X = X;
	this->Y = Y;
	Width = 20;
	Height = 30;
	Life = 100;
	Angle = 0;
	Jumping = false;
}

Player::~Player()
{
}
