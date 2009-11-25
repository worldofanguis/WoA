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
#include "Units/ObjectMgr.h"


// TODO: This whole stuff should be wrapped in a class (or whatever) //

bool Running = true;
DirectXInterface DXI;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);		// We wont use these paramters //
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Register the window class //
	WNDCLASSEX WinClass;
	WinClass.cbSize = sizeof(WNDCLASSEX);
	WinClass.style = CS_CLASSDC;
	WinClass.lpfnWndProc = WndProc;
	WinClass.cbClsExtra = 0;
	WinClass.cbWndExtra = 0;
	WinClass.hInstance = hInstance;
	WinClass.hIcon = LoadIcon(hInstance,IDI_APPLICATION);
	WinClass.hIconSm = LoadIcon(hInstance,IDI_APPLICATION);
	WinClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	WinClass.hbrBackground = NULL;
	WinClass.lpszMenuName = NULL;
	WinClass.lpszClassName = "WoA";
	RegisterClassEx(&WinClass);

	HWND hwnd;
	// Create the application's window //
	if((hwnd = CreateWindow("WoA", "woa",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,0,0,1024,768,HWND_DESKTOP,NULL,hInstance,NULL)) == NULL)
		{
		MessageBox(NULL,"Failed to create the main window","Oops",MB_OK);
		return 0;
		}

	// Initialize the DXInterface //
	if(SUCCEEDED(DXI.Initialize(hwnd,true)))
		{
		// Testing initializations (TODO: Remove these) //
		sObjMgr->AddPlayer(30,70,1);
		sObjMgr->AddPlayer(30,150,1);
		sObjMgr->CreateWorld();
		
		// Show the window //
		ShowWindow(hwnd,nCmdShow);
		UpdateWindow(hwnd);

		// Enter the message loop //
		MSG msg;
		while(Running)
			{
			if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
				{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				}
				
			sObjMgr->Update();
			DXI.Render();
			Sleep(10);			// To reduce CPU usage from 100% //
			}
		}
	else
		MessageBox(hwnd,"Failed to initialize Direct3D!","Oops",MB_OK);


	delete sObjMgr;		// Err, not sure where to put this ^^ <if needed at all> //
	
	// Cleanup the DXInterface //
	DXI.Cleanup();

	UnregisterClass("WoA",hInstance);		// Unregister our window's class //

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
return 0;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
		{
		case WM_TIMER:
		case WM_DESTROY:
			PostQuitMessage(0);
			Running = false;
			return 0;
			
		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				{
				Running = false;
				return 0;
				}

			else if(wParam == 'W')
				reinterpret_cast<Player*>(sObjMgr->Me())->AddYVelocity(-5);
			else if(wParam == 'S')
				reinterpret_cast<Player*>(sObjMgr->Me())->AddYVelocity(5);
			else if(wParam == 'A')
				reinterpret_cast<Player*>(sObjMgr->Me())->AddXVelocity(-5);
			else if(wParam == 'D')
				reinterpret_cast<Player*>(sObjMgr->Me())->AddXVelocity(5);
			
			else if(wParam == 'R')
				reinterpret_cast<Player*>(sObjMgr->Me())->SetPos(30,70);

			else if(wParam == VK_DOWN)
				DXI.ScrollDown(5);
			else if(wParam == VK_UP)
				DXI.ScrollUp(5);
			else if(wParam == VK_LEFT)
				DXI.ScrollLeft(5);
			else if(wParam == VK_RIGHT)
				DXI.ScrollRight(5);
			else if(wParam == VK_PRIOR)
				{
				reinterpret_cast<Player*>(sObjMgr->Me())->SetLife(reinterpret_cast<Player*>(sObjMgr->Me())->GetLife()-1);
				sHud->Update(DXHUDView::HUD_LIFE,reinterpret_cast<Player*>(sObjMgr->Me())->GetLife());
				}
			else if(wParam == VK_NEXT)
				{
				reinterpret_cast<Player*>(sObjMgr->Me())->SetLife(reinterpret_cast<Player*>(sObjMgr->Me())->GetLife()+1);
				sHud->Update(DXHUDView::HUD_LIFE,reinterpret_cast<Player*>(sObjMgr->Me())->GetLife());
				}				
			break;
		}

return DefWindowProc(hWnd, msg, wParam, lParam);
}
