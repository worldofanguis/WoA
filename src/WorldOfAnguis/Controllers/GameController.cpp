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
	ViewWidth = sDXInterface->GetViewWidth();
	ViewHeight = sDXInterface->GetViewHeight();
	
	ViewLeft = ViewTop = 0;
	Run();
}

GameController::~GameController()
{
	delete sObjMgr;
}

void GameController::Run()
{
	new Player(30,70,1);
	new Player(80,60,1);
	
	sObjMgr->CreateWorld();
	sObjMgr->Update();

    DWORD realCurrTime = 0;
    DWORD realPrevTime = GetMSTime();

	DWORD diff;
	
	/* Example for using the sScreenLog class */
	sScreenLog->AddTrack(&diff,ScreenLog::Track::UINT,20,30,0xFFFF0000);
	
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
				new Explosion(me->GetX()+4,me->GetY()+(me->GetHeight()/2),19,0);
			}
		}
		if(KEY_DOWN(DIK_D)){
			me->SetXVelocity(3);
			if(KEY_DOWN(DIK_A)){
				new Explosion(me->GetX()+me->GetWidth()-4,me->GetY()+(me->GetHeight()/2),19,0);
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
		
		if(KEY_PRESSED(DIK_B))
			new Explosion(80,60,15,30);
		if(KEY_PRESSED(DIK_N))
			new Explosion(150,150,50,30);
			
		if(KEY_DOWN(DIK_M))
			 sWorld->PrintMap();

		if(KEY_DOWN(DIK_SPACE))
			{
			me->SetXVelocity(0);
			me->SetYVelocity(0);
			}

		sObjMgr->Update();
		FollowUnit(me);
		Render(diff);

		realPrevTime = realCurrTime;
		}
}

void GameController::Render(DWORD diff)
{
	DirectXInterface* DXI = sDXInterface;
	DXI->BeginScene();

	// Drawing the world //
	sWorldView->Draw(ViewLeft,ViewTop,ViewWidth,ViewHeight);
	// Drawing the HUD //
	sHudView->Draw();
	// Drawing the Objects via the DrawMgr //
	sDrawMgr->Draw(ViewLeft,ViewTop);
	
	/* Example for using the sSceenLog class */
//	sScreenLog->DrawNow(&diff,ScreenLog::Track::UINT,20,30,0xFFFF0000);
	
	DXI->EndScene();
}

/* NOTE: I modified the fuction (sry) cause this way it can be used to 
 *		 follow bullets too (like contollable missiles etc)
 */
void GameController::FollowUnit(Unit *unit) 
{
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