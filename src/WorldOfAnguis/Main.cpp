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


#ifdef _DEBUG
#define __SHOW_STUPID_WARNINGS__
#endif

#include "Common.h"
#include "Graphics/DirectX/DirectXInterface.h"
#include "Controllers/GameController.h"

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	if(OpenMutex(MUTEX_ALL_ACCESS,false,"WoA") != NULL)			// Disable multiple starting //
		{
		MessageBox(HWND_DESKTOP,"Use the power of alt-tab","I'm already running...",MB_OK);
		return 1;
		}
	HANDLE hMutex = CreateMutex(NULL,false,"WoA");
	
	if(FAILED(sDXInterface->Initialize(hInstance,true)))		// Initializing the DirectX interface:
		{														//	creating window, and d3d device
		MessageBox(HWND_DESKTOP,"U FAIL!",">_<",MB_OK);
		return 0;
		}

	delete new GameController();		// Initializing the main class, 
										//	later it should be replaced with the main menu
	
	// Cleanup //
	sDXInterface->Cleanup();
	
	delete sDXInterface;
	
	ReleaseMutex(hMutex);
	
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
return 0;
}

