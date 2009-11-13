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

class Player : public Unit
{
public:
	Player(int X = 0,int Y = 0);
	~Player();

	int GetLife() {return Life;}
	void DecreaseLife(int Damage) {if(Life >= Damage) {Life-=Damage;} else {Life = 0;}}
	void SetLife(int Life) {this->Life = Life;}
	
	/* Set the player position (not sure we'll need it later) */
	void AddXVelocity(int v) {vX+=v;}
	void AddYVelocity(int v) {vY+=v;}
	
	void SetPos(int X,int Y) {this->X = X; this->Y = Y;}
	
	float GetAngle() {return Angle;}
	bool GetJumping() {return Jumping;}

private:
	float Angle;
	int Life;
	bool Jumping;
};
