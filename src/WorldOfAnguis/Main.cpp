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


#define __SHOW_STUPID_WARNINGS__		// Debug //
 
#include "Common.h"
#include "Graphics/DirectX/DirectXInterface.h"
#include "Controllers/GameController.h"


int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	if(FAILED(sDXInterface->Initialize(hInstance,true)))
		{
		MessageBox(HWND_DESKTOP,"U FAIL!",">_<",MB_OK);
		return 0;
		}

	delete new GameController();		// Nice stuff ^^ //
	
	// Cleanup //
	KeyboardController::Release();
	sDXInterface->Cleanup();
	
	delete sDXInterface;
	
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
return 0;
}
