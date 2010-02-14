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


#include "GameController.h"
#include "Units/ObjectMgr.h"
#include "Graphics/DirectX/DirectXInterface.h"
#include "Units/Explosion/Explosion.h"
#include "World/World.h"
#include "Time.h"

GameController::GameController()
{
	ViewWidth = sDXInterface->GetViewWidth();		// Getting resolution parameters //
	ViewHeight = sDXInterface->GetViewHeight();
	
	ViewLeft = ViewTop = 0;
	Run();						// Starts the main loop //
}

GameController::~GameController()
{
	delete sObjMgr;				// Destroying the only object we created //
}

void GameController::Run()
{
	Player* me = new Player(0,0,1);

	sObjMgr->CreateWorld();
	sObjMgr->Update();

    DWORD realCurrTime = 0;
    DWORD realPrevTime = GetMSTime();

	DWORD diff;

	/* Example for using the sScreenLog class */
	sScreenLog->AddTrack(&diff,ScreenLog::Track::UINT,20,30,0xFFFF0000);
	
//	sScreenLog->AddTrack(&me->X,ScreenLog::Track::INT,20,50,0xFFFF0000);
//	sScreenLog->AddTrack(&me->Y,ScreenLog::Track::INT,20,70,0xFFFF0000);
	while(true)
		{
		realCurrTime = GetMSTime();
		diff = GetMSTimeDiff(realPrevTime,realCurrTime);

		Player* me = sObjMgr->Me();

		ReadKeyboard();

		if(KEY_PRESSED(DIK_F))
			me->Fire();

		if(KEY_DOWN(DIK_ESCAPE))
			break;
		if(KEY_DOWN(DIK_W))
			me->SetYVelocity(-3);
		if(KEY_DOWN(DIK_S))
			me->SetYVelocity(3);
		if(KEY_DOWN(DIK_A)){
			me->SetXVelocity(-3);
			if(KEY_DOWN(DIK_D)){
				new Explosion(me,me->GetX()+4,me->GetY()+(me->GetHeight()/2),19,0,false);
			}
		}
		if(KEY_DOWN(DIK_D)){
			me->SetXVelocity(3);
			if(KEY_DOWN(DIK_A)){
				new Explosion(me,me->GetX()+me->GetWidth()-4,me->GetY()+(me->GetHeight()/2),19,0,false);
			}
		}

		/* Oops :< */
		//if(KEY_UP(DIK_W) && KEY_UP(DIK_A) && KEY_UP(DIK_S) && KEY_UP(DIK_D))
		//	{
		//	me->SetXVelocity(0);
		//	me->SetYVelocity(0);
		//	}

		if(KEY_DOWN(DIK_R))
			me->SetPos(30,70);

		if(KEY_DOWN(DIK_Q))
			me->SetAngle(me->GetAngle()+0.1f);

		if(KEY_DOWN(DIK_E))
			me->SetAngle(me->GetAngle()-0.1f);

		if(KEY_DOWN(DIK_M))
			 sWorld->PrintMap();

		if(KEY_DOWN(DIK_SPACE))
			{
			me->SetXVelocity(0);
			me->SetYVelocity(0);
			}

		sObjMgr->Update(/* diff */);
		FollowUnit(me);
		Render();

		realPrevTime = realCurrTime;
		}
}

void GameController::Render()
{
	DirectXInterface* DXI = sDXInterface;		// Retrieve the Interface we use for drawing //
	DXI->BeginScene();

	// Drawing the world //
	sWorldView->Draw(ViewLeft,ViewTop,ViewWidth,ViewHeight);		// Render the world //
	// Drawing the Objects via the DrawMgr //
	sDrawMgr->Draw(ViewLeft,ViewTop);								// the objects //
	// Drawing the HUD //
	sHudView->Draw();												// and the hud //

	DXI->EndScene();
}

/* NOTE: I modified the fuction (sry) cause this way it can be used to 
 *		 follow bullets too (like contollable missiles etc)
 */
void GameController::FollowUnit(Unit *unit) 
{
	if(unit == NULL)
		return;

	int x = unit->GetX();
	int y = unit->GetY();
	int h = sWorld->GetHeight();
	int w = sWorld->GetWidth();

	// ViewLeft 
	if ( x - ViewWidth/2 < 0 )
		ViewLeft = 0;
	else if ( x + ViewWidth/2 > w )
		ViewLeft = w - ViewWidth;
	else
		ViewLeft = x - ViewWidth/2;

	// ViewTop
	if ( y - ViewHeight/2 < 0 )
		ViewTop = 0;
	else if ( y + ViewHeight/2 > h)
		ViewTop = h - ViewHeight;
	else
		ViewTop = y - ViewHeight/2;
}