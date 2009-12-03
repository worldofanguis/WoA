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
	if(OpenMutex(MUTEX_ALL_ACCESS,false,"WoA") != NULL)
		{
		MessageBox(HWND_DESKTOP,"Use the power of alt-tab","I'm already running...",MB_OK);
		return 1;
		}
	HANDLE hMutex = CreateMutex(NULL,false,"WoA");
	
	if(FAILED(sDXInterface->Initialize(hInstance,true)))
		{
		MessageBox(HWND_DESKTOP,"U FAIL!",">_<",MB_OK);
		return 0;
		}

	delete new GameController();		// Nice stuff ^^ //
	
	// Cleanup //
	sDXInterface->Cleanup();
	
	delete sDXInterface;
	
	ReleaseMutex(hMutex);
	
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
return 0;
}
