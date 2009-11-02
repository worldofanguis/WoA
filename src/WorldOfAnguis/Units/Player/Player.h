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
#include "../Unit.h"
#include "Graphics/Units/Player/DXPlayerView.h"

class Player : public Unit , DXPlayerView
{
public:
	Player(int X = 0,int Y = 0);
	~Player();

	/* Call the View class draw function to draw the player on the screen (substact the viewX,viewY to position on the MAP and not on the SCREEN) */
	void Draw(int ViewX,int ViewY) {DXPlayerView::Draw(X-ViewX,Y-ViewY,Jumping);}

	/* Set the player position (not sure we'll need it later) */
	void SetPos(int X,int Y) {this->X = X; this->Y = Y;}

private:
	bool Jumping;
};
