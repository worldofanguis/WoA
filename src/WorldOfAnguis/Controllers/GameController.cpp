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
	sObjMgr->AddPlayer(30,70,1);
	sObjMgr->AddPlayer(30,150,1);
	sObjMgr->CreateWorld();

	while(true)
		{
		ReadKeyboard();
		if(KEY_DOWN(DIK_ESCAPE))
			break;

		sObjMgr->Update();
		
		Render();
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
