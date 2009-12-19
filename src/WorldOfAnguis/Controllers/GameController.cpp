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
			 
		/*if(KEY_DOWN(DIK_LEFT))
			ScrollLeft(5);
		if(KEY_DOWN(DIK_RIGHT))
			ScrollRight(5);
		if(KEY_DOWN(DIK_UP))
			ScrollUp(5);
		if(KEY_DOWN(DIK_DOWN))
			ScrollDown(5);*/

		if(KEY_DOWN(DIK_SPACE))
			{
			me->SetXVelocity(0);
			me->SetYVelocity(0);
			}

		sObjMgr->Update();
		FollowPlayer(me);
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

/* Maybe this functions should be moved to 2 (ScrollingVertical and ScrollingHorizontal) */
void GameController::ScrollLeft(int Dist)
{
	if(ViewLeft-Dist > 0)
		ViewLeft -= Dist;
	else
		ViewLeft = 0;
}

void GameController::ScrollRight(int Dist)
{
	if(ViewLeft+ViewWidth+Dist < sWorld->GetWidth())
		ViewLeft += Dist;
	else
		ViewLeft = sWorld->GetWidth()-ViewWidth;
}

void GameController::ScrollUp(int Dist)
{
	if(ViewTop-Dist > 0)
		ViewTop -= Dist;
	else
		ViewTop = 0;
}

void GameController::ScrollDown(int Dist)
{
	if(ViewTop+ViewHeight+Dist < sWorld->GetHeight())
		ViewTop += Dist;
	else
		ViewTop = sWorld->GetHeight()-ViewHeight;
}

void GameController::FollowPlayer(Player *p) 
{
	int x = p->GetX();
	int y = p->GetY();
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