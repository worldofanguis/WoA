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
	Player();
	Player(int X,int Y);
	~Player();

	void Update();
	void Draw(int ViewX,int ViewY) {DXPlayerView::Draw(X-ViewX,Y-ViewY);}

	void SetPos(int X,int Y) {this->X = X; this->Y = Y;}

private:
	
};
