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

    DWORD realCurrTime = 0;
    DWORD realPrevTime = getMSTime();

    DWORD prevSleepTime = 0;                               // used for balanced full tick time length near SLEEP_CONS	
	DWORD diff;
		
	while(true)
		{
        realCurrTime = getMSTime();
		diff = getMSTimeDiff(realPrevTime,realCurrTime);

		Player* me = sObjMgr->Me();
		ReadKeyboard();
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
			
		if(KEY_DOWN(DIK_B))
			new Explosion(80,60,15,30);
		if(KEY_DOWN(DIK_N))
			new Explosion(150,150,50,30);
			
		if(KEY_DOWN(DIK_M))
			 sWorld->PrintMap();
			 
		if(KEY_DOWN(DIK_LEFT))
			ScrollLeft(5);
		if(KEY_DOWN(DIK_RIGHT))
			ScrollRight(5);
		if(KEY_DOWN(DIK_UP))
			ScrollUp(5);
		if(KEY_DOWN(DIK_DOWN))
			ScrollDown(5);

		if(KEY_DOWN(DIK_SPACE))
			{
			me->SetXVelocity(0);
			me->SetYVelocity(0);
			}

		sObjMgr->Update();	
		Render();
		
		realPrevTime = realCurrTime;
		if (diff <= SLEEP_CONST+prevSleepTime)
			{
			prevSleepTime = SLEEP_CONST+prevSleepTime-diff;
			Sleep(prevSleepTime);
			}
		else
			prevSleepTime = 0;
		}
}

void GameController::Render()
{
	DirectXInterface* DXI = sDXInterface;
	DXI->BeginScene();

	// Drawing the world //
	sWorldView->Draw(ViewLeft,ViewTop,ViewWidth,ViewHeight);
	// Drawing the HUD //
	sHudView->Draw();
	// Drawing the Objects via the DrawMgr //
	sDrawMgr->Draw(ViewLeft,ViewTop);

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
