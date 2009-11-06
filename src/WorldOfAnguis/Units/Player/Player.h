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


//#pragma once

#ifndef __Player__
#define __Player__

#include "../Unit.h"
class DXPlayerView;
#include "Graphics/DirectX/Units/Player/DXPlayerView.h"

class Player : public Unit
{
public:
	Player(int X = 0,int Y = 0);
	~Player();

	int GetLife() {return Life;}
	void DecreaseLife(int Damage) {if(Life >= Damage) {Life-=Damage;} else {Life = 0;}}
	void SetLife(int Life) {this->Life = Life;}
	
	/* Call the View class draw function to draw the player on the screen (substact the viewX,viewY to position on the MAP and not on the SCREEN) */
	void Draw(int ViewX,int ViewY) {View.Draw(X-ViewX,Y-ViewY,FaceRight,Jumping);}

	/* Set the player position (not sure we'll need it later) */
	void SetPos(int X,int Y) {this->X = X; this->Y = Y;}

private:
	DXPlayerView View;
	float Angle;
	int Life;
	bool Jumping;
};

#endif