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
	Player(int X,int Y,int SkinID);
	~Player();
	bool CollideX();

	int GetLife() {return Life;}
	void DecreaseLife(int Damage) {if(Life >= Damage) {Life-=Damage;} else {Life = 0;}}
	void SetLife(int Life) {this->Life = Life;}
	
	/* Set the player position (not sure we'll need it later) */
	void SetXVelocity(int v) {vX=v;}
	void SetYVelocity(int v) {vY=v;}
	
	void SetPos(int X,int Y) {this->X = X; this->Y = Y;}
	void SetAngle(float Angle) {this->Angle = Angle;}
	
	float GetAngle() {return Angle;}
	bool GetJumping() {return Jumping;}
	
	void Fire();
	
private:
	float Angle;
	int Life;
	bool Jumping;
};
