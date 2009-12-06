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


#include "Unit.h"
#include "Units/ObjectMgr.h"

Unit::Unit(int X,int Y,TYPES Type)
{
	this->X = X;
	this->Y = Y;
	this->Type = Type;
	
	vX = vY = 0;
	Width = Height = 0;
	
	sObjMgr->RegisterUnit(this);
}

Unit::~Unit()
{
}

void Unit::Update()
{
//	X+=vX;
//	Y+=vY;
}

bool Unit::CollisionUnit(Unit* unit)
{
	if(unit == this)	// We dont want to check collision with self ^^ //
		return false;

	int SelfCX,SelfCY,UnitCX,UnitCY;
	SelfCX = X+vX+(Width/2);
	SelfCY = Y+vY+(Height/2);
	UnitCX = unit->X+(unit->Width/2);
	UnitCY = unit->Y+(unit->Height/2);
	if((abs(SelfCX-UnitCX) < max(Width,unit->Width)) && abs(SelfCY-UnitCY) < max(Height,unit->Height))
		{
		vX = 0;			// Stop the target (at least for now) //
		vY = 0;
		return true;
		}

return false;
}

bool Unit::CollisionWorld()
{	
	//vY+=1;
	if(vX == 0 && vY == 0)		// We dont move since we dont have any velocity //
		return false;
	bool Collided = false;
	/*Its important that the collision detection on Y run first
	 *because it may set vY to zero before X movement is tested.
	 *This way moving on a horizontal surface will test only on the X axis
	 */


	if(CollideY()){
		Collided = true;
		vY=0;
	}
	if(CollideX()){
		Collided = true;
		vX=0;
	}
	//X += vX;
	//Y += vY;
	

return Collided;
}

bool Unit::CollidePoint(int x_rel, int y_rel, int* xf, int* yf){
	bool Collided=false;
	int x0,x1,y0,y1; //new coord.
	x0=X+x_rel; x1=x0+vX;
	y0=Y+y_rel; y1=y0+vY;

	int dx, dy;
	dx=x1-x0;
	dy=y1-y0;
	
	/*Using variables for testing we will be able to set the final position
	 *to the last available coordinates*/
	int xt, yt;

	/*(not so) simple linedrawing algorithm parses the path ahead
	 *and stops when HitTest is true for the actual point*/
	float t = (float) 0.5;                      // offset for rounding
	xt=x0;
	yt=y0;

      if ((dx>0?dx:-dx) > (dy>0?dy:-dy)) {          // slope < 1
      float m = (float) dy / (float) dx;			// compute slope
            t += y0;
            dx = (dx < 0) ? -1 : 1;
            m *= dx;
            while (xt != x1) {
                xt += dx;                           // step to next x value
                t += m;                             // add slope to y value
                if(HitTest(xt,(int)t)){
					Collided = true;
					break;
				}else{
					x0=xt;
					y0=(int)t;
				}
			}
		} else {                                    // slope >= 1
            float m = (float) dx / (float) dy;      // compute slope
            t += x0;
            dy = (dy < 0) ? -1 : 1;
            m *= dy;
            while (yt != y1) {
                yt += dy;                           // step to next y value
                t += m;                             // add slope to x value
                if(HitTest((int)t,yt)){
					Collided = true;
					break;
				}else{
					x0=int(t);
					y0=yt;
				}
			}
		}



		if(x0==x1 && y0==y1)
			Collided = false;	//if it reached the destination, there was no collision
		*xf = x0;
		*yf = y0;

		return Collided;
}

bool Unit::CollidePlayerPoint(int x, int y, int* xf, int* yf){
	bool hit=false;
	int xt, yt, dx;
	int x_final, y_final;
	x_final=x+vX;
	y_final=y;

	if(!vY && vX){	//JUMPING attribute should go here (if there's no vX no testing is required)
		
		if(vX>0){
			dx=1;
		}
		else{
			dx=-1;
		}
		xt=x;

		while(xt!=x+vX){
			
			xt+=dx;
			yt=y_final;
			if(HitTest(xt, yt)){
				for(int i=3; i>0; i--){ //instead of 3 there should be MAXSTEEP defined in UNIT.h
					if(!HitTest(xt,yt-i) && !HitTestBorder(xt-Width, yt-i-Height, false, false) && !HitTestBorder(xt-Width, yt-i-Height, true, true))
							y_final=yt-i;
					else{
						hit=true; break;
					}
					
				}
			}
			if(hit){
				break;
				x_final=xt-dx;
			}
		}
	}
	*xf=x_final;
	*yf=y_final;
	return hit;

}

bool Unit::HitTest(int x, int y){
	char* Map = sWorld->GetHitMap();
	int PPHM = sWorld->GetPixelPerHitMap();
	int MapWidth = sWorld->GetHitMapWidth();

	int x0=x;
	int y0=y;

	if(x0 >= sWorld->GetWidth() || x0<0)
		return true;	//X out of bounds
	if(y0 >= sWorld->GetHeight() || y0<0)
		return true;	//Y out of bounds
	if(Map[((y0/PPHM)*MapWidth)+(x0/PPHM)] > 0)
		return true;	//HitMap collision
	return false;

}

bool Unit::HitTestBorder(int x, int y, bool right, bool down){
	for(int y0=0;y0<=Height;y0++){
		if(HitTest(x+(int)right*Width,y0)){
			return true;
		}
	}

	for(int x0=0;x0<=Width;x0++){
		if(HitTest(x0,y+int(down)*Height)){
			return true;		
		}		
	}
	return false;

	
}

bool Unit::Collide(){
	bool Collided=false;
	/*The point to be tested relative to position*/
	int xt,yt;
	if(vX>0)xt=Width;
	else xt=0;

	if(vY>0)yt=Height;
	else yt=0;

	/*where can we go??*/
	int xf, yf, x_final=X+vX, y_final=Y+vY;
	if(vX!=0)
	for(int y0=0;y0<=Height;y0++){
		if(CollidePoint(xt,y0,&xf,&yf)){
			Collided=true;
			if(vX>0){	//going to the right - 
				//we have to take the minimum of the possible x values
				if(x_final>xf-Width)x_final=xf-Width;
			}
			else{
				if(x_final<xf)x_final=xf;	//maximum of the possible x values
			}
			
		}
	}
	

	if(vY!=0)
	for(int x0=0;x0<=Width;x0++){
		if(CollidePoint(x0,yt,&xf,&yf)){
			Collided=true;
			if(vY>0){	//going down - 
				//we have to take the minimum of the possible y values
				if(y_final>yf-Height)y_final=yf-Height;
			}
			else{
				if(y_final<yf)y_final=yf;	//maximum of the possible y values
			}
			
		}
		
	}
	
	X=x_final;
	Y=y_final;
	
	return Collided;
}

bool Unit::CollideX(){
	bool Collided=false;
	/*The point to be tested relative to position*/
	int xt,yt;
	if(vX>0)xt=Width;
	else xt=0;

	if(vY>0)yt=Height;
	else yt=0;

	/*where can we go??*/
	int xf, yf, x_final=X+vX, y_final=Y+vY;
	if(vX!=0)
	for(int y0=0;y0<=Height;y0++){
		if(CollidePoint(xt,y0,&xf,&yf)){
			Collided=true;
			if(vX>0){	//going to the right - 
				//we have to take the minimum of the possible x values
				if(x_final>xf-Width)x_final=xf-Width;
			}
			else{
				if(x_final<xf)x_final=xf;	//maximum of the possible x values
			}
			
		}
	}
	

	if(vY!=0)
	for(int x0=0;x0<=Width;x0++){
		if(CollidePoint(x0,yt,&xf,&yf)){
			//Collided=true;
			if(vY>0){	//going down - 
				//we have to take the minimum of the possible y values
				if(y_final>yf-Height)y_final=yf-Height;
			}
			else{
				if(y_final<yf)y_final=yf;	//maximum of the possible y values
			}
			
		}
		
	}
	
	X=x_final;
	//Y=y_final;
	
	return Collided;
}

bool Unit::CollideY(){
	bool Collided=false;
	/*The point to be tested relative to position*/
	int xt,yt;
	if(vX>0)xt=Width;
	else xt=0;

	if(vY>0)yt=Height;
	else yt=0;

	/*where can we go??*/
	int xf, yf, x_final=X+vX, y_final=Y+vY;
	if(vX!=0)
	for(int y0=0;y0<=Height;y0++){
		if(CollidePoint(xt,y0,&xf,&yf)){
			//Collided=true;
			if(vX>0){	//going to the right - 
				//we have to take the minimum of the possible x values
				if(x_final>xf-Width)x_final=xf-Width;
			}
			else{
				if(x_final<xf)x_final=xf;	//maximum of the possible x values
			}
			
		}
	}
	

	if(vY!=0)
	for(int x0=0;x0<=Width;x0++){
		if(CollidePoint(x0,yt,&xf,&yf)){
			Collided=true;
			if(vY>0){	//going down - 
				//we have to take the minimum of the possible y values
				if(y_final>yf-Height)y_final=yf-Height;
			}
			else{
				if(y_final<yf)y_final=yf;	//maximum of the possible y values
			}
			
		}
		
	}
	
	//X=x_final;
	Y=y_final;
	
	return Collided;
}



