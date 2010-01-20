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
#include "Units/ObjectMgr.h"
#include "Units/Explosion/Explosion.h"
#include "Graphics/DirectX/DirectXInterface.h"

Player::Player(int X,int Y,int SkinID) : Unit(X,Y,PLAYER)
{
	Width = 20;
	Height = 30;
	Life = 100;
	Angle = 0;
	Jumping = false;
	
	Score = 0;
	
	char PlayerTexture[MAX_PATH];
	sprintf_s(PlayerTexture,sizeof(PlayerTexture),"..\\..\\pic\\Player\\Player%d.bmp",SkinID);
	sDrawMgr->RegisterUnit((Unit*)this,PlayerTexture);
}

Player::~Player()
{

}

void Player::Fire()
{
	new Bullet(this,(X+(Width/2))+cos(Angle)*35,(Y+(Height/2))-sin(Angle)*35,Angle,Bullet::DEFAULT);
}

bool Player::CollideX(int* xreturn){
	
	if((!Jumping) && vX){
		int xf, yf;
		bool Collided = false;
		if(vX>0){
			Collided = CollidePlayerPoint(X+Width, Y+Height, &xf, &yf);
			X=xf-Width; Y = yf-Height;
		}else{
			Collided = CollidePlayerPoint(X, Y+Height, &xf, &yf);
			X=xf; Y = yf-Height;
		}
		*xreturn=X;
		return Collided;
	}
	else{
		return Unit::CollideX(xreturn);
	}
}

bool Player::CollisionWorld(){

	if(vYd<1)vYd+=GRAVITY;
	else vYd=0.0;
	vY+=(int)vYd;

	if(vX == 0 && vY == 0)		// We dont move since we dont have any velocity //
		return false;
	bool Collided = false;
	/*Its important that the collision detection on Y run first
	 *because it may set vY to zero before X movement is tested.
	 *This way moving on a horizontal surface will test only on the X axis
	*/
	/*But it's still buggy, because if we test Y first, hitting a vertical
	 *surface will cause a Y collision which we dont want.
	 *I think the solution would be testing the angle of the hit surface. Once we will
	 *do that if we want bullets to bounce. If we dont, i have no idea how to solve
	 *this problem.
	*/

	int xf, yf;

	if(CollideY(&yf)){
		Collided = true;
		if(vY>0)	//We set Jumping false only if we were falling down
			Jumping=false;
		vYd=0;
		vY=0;
		
		
	}
	
	else if(vY>2 || vY<-2)
		Jumping=true;
	Y=yf;
	if(CollideX(&xf)){
		Collided = true;
		vX=0;
	}
	X=xf;
	

	return Collided;
}


bool Player::CollidePlayerPoint(int x, int y, int* xf, int* yf){
	bool hit=false;
	int xt, yt, dx;
	int x_final, y_final;
	x_final=x+vX;
	y_final=y;

	if(!Jumping && vX){	//(if there's no vX no testing is required)
			
		if(vX>0){
			dx=1;
		}
		else{
			dx=-1;
		}
		xt=x;

		bool step=false;
		while(xt!=x+vX){
			
			xt+=dx;
			yt=y_final;
			if(HitTest(xt, yt)){
				for(int i=MAXSTEEP; i>0; i--){
					if(!HitTest(xt,yt-i) && !HitTestBorder(vX>0?xt-Width:xt, yt-i-Height, false, false) && !HitTestBorder(vX>0?xt-Width:xt, yt-i-Height, true, true))
							y_final=yt-i;
					else{
						if(i==MAXSTEEP)	//instead of 3 MAXSTEEP
							hit=true;
						break;
					}
					
				}
			}
			else{	//if the leg didn't hit the ground
				
				for(int i=-1; i>-MAXSTEEP-1; i--){
					if(!HitTest(vX>0?xt-Width:xt+Width,yt-i) && !HitTestBorder(vX>0?xt-Width:xt, yt-i-Height, false, false) && !HitTestBorder(vX>0?xt-Width:xt, yt-i-Height, true, true))
							y_final=yt-i;
					else{
						step=true;
						break;
					}
					
				}
				if(!step){
					Jumping=true;
					y_final-=(MAXSTEEP-1);
				}

			}

			if(hit){				
				x_final=xt-dx;
				break;
			}
		}
	}
	*xf=x_final;
	*yf=y_final;
	return hit;
}

bool Player::CollisionUnit(Unit* unit)
{
	if(Unit::CollisionUnit(unit))
		{	// we collided with the unit, stop ourselves //
		vX = vY = 0;
		}

return false;	// whatever, it doesnt matter //
}

void Player::Explode(Unit* explosion)
{
	int SelfCX = X+(Width/2);
	int SelfCY = Y+(Height/2);
	int ExpCX = explosion->GetX()+(explosion->GetWidth()/2);
	int ExpCY = explosion->GetY()+(explosion->GetHeight()/2);

	if((abs(SelfCX-ExpCX) < max(Width,explosion->GetWidth())) && abs(SelfCY-ExpCY) < max(Height,explosion->GetHeight()))
		{		// We are in the range of an explosion //
		if(reinterpret_cast<Explosion*>(explosion)->GetDamage() == 0)
			return;		// Nothing to do with explosions that do no damage //

//		float Distance = sqrt(float(((SelfCX-ExpCX)*(SelfCX-ExpCX)) + ((SelfCY-ExpCY)*(SelfCY-ExpCY))));
		int DamageDone = reinterpret_cast<Explosion*>(explosion)->GetDamage();		// (reinterpret_cast<Explosion*>(explosion)->GetDamage() / Distance) + 1;
		
		Life-=DamageDone;
		if(Life <= 0)
			{		// We've just died :( //
			if(reinterpret_cast<Explosion*>(explosion)->GetCreator() == this)
				{		// Omg we killed ourselves ... //
				SetScore(-1);		// We deserve it //
				}
			else
				reinterpret_cast<Explosion*>(explosion)->GetCreator()->SetScore(+1);
			Life = 100;		// Respawn
			}
		if(this == sObjMgr->Me())
			sHudView->Update(DXHUDView::HUD_LIFE,Life);		// Update our hud //
		}
}