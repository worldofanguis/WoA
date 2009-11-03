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


// TODO: This whole stuff should be wrapped in a class (or whatever) //

DirectXInterface DXI;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);		// We wont use this paramters //
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
		World W;
		W.LoadMaps(NULL,"..\\..\\pic\\Map.bmp");
		// Show the window //
		ShowWindow(hwnd,nCmdShow);
		UpdateWindow(hwnd);

		// Enter the message loop //
		MSG msg; 
		while(GetMessage(&msg,NULL,0,0))
			{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			}
		}
	else
		MessageBox(hwnd,"Failed to initialize Direct3D!","Oops",MB_OK);

    // Cleanup the DXInterface //
    DXI.Cleanup();

    UnregisterClass("WoA",hInstance);		// Unregister our window's class //
return 0;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
		{
		case WM_TIMER:
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			
		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				{
				PostQuitMessage(0);
				return 0;
				}
			else if(wParam = VK_DOWN)
				DXI.ScrollDown(10);
			break;

		case WM_PAINT:
			DXI.Render();
			return 0;
		}

return DefWindowProc(hWnd, msg, wParam, lParam);
}
