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
 
 
#include "../Unit.h"
#include "Graphics/Units/Player/DXPlayerView.h"

class Player : public Unit , private DXPlayerView
{
public:
	Player() {Width = 20; Height = 30;}
	Player(int X,int Y) {this->X = X; this->Y = Y;Width = 20; Height = 30;}
	~Player();

	void Update();
	void Draw(int ViewX,int ViewY) {DXPlayerView::Draw(X-ViewX,Y-ViewY);}
	
	void SetPos(int X,int Y) {this->X = X; this->Y = Y;}
	
private:
	
};
