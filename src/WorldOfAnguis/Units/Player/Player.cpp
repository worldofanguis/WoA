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

//bool Player::CollideX(){
//	if(!vY && vX){	//!JUMPING should go here
//		int xf, yf;
//		bool Collided = false;
//		if(vX>0){
//			Collided = CollidePlayerPoint(X+Width, Y+Height, &xf, &yf);
//		}else
//			Collided = CollidePlayerPoint(X, Y+Height, &xf, &yf);
//		X=xf-Width; Y = yf-Height;
//		return Collided;
//	}
//	else{
//		return Unit::CollideX();
//	}
//
//}
bool Player::CollideX(){
	return Unit::CollideX();
}


