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
		sDXInterface->Render();
		}
}