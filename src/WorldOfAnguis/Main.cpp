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

DirectXInterface DXI;
World w;
Player p;
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// Register the window class
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

    // Create the application's window
    HWND hwnd = CreateWindow("WoA", "woa",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,100,100,500,500,HWND_DESKTOP,NULL,hInstance,NULL);

	// Initialize Direct3D
	if(SUCCEEDED(DXI.Initialize(hwnd)))
		{
		w.LoadMaps(NULL,"..\\..\\pic\\Map.bmp");
		DXI.RegisterWorld(&w);
		p.SetPos(10,10);
		DXI.RegisterUnit(reinterpret_cast<Unit*>(&p));
		// Show the window
		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);

		// Enter the message loop
		MSG msg; 
		while(GetMessage(&msg,NULL,0,0))
			{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			}
		}
	else
		MessageBox(hwnd,"Failed to initialize Direct3D!","Oops",MB_OK);

    // Clean up everything and exit the app
    DXI.Cleanup();

    UnregisterClass("WoA",hInstance);
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

		case WM_PAINT:
			DXI.Render();
			return 0;
		case WM_KEYDOWN:
			if(wParam == VK_LEFT)
				DXI.ScrollLeft(2);
			else if(wParam == VK_RIGHT)
				DXI.ScrollRight(2);
			else if(wParam == VK_UP)
				DXI.ScrollUp(2);
			else if(wParam == VK_DOWN)
				DXI.ScrollDown(2);

			if(wParam == 'A')
				p.SetPos(p.GetX()-2,p.GetY());
			else if(wParam == 'D')
				p.SetPos(p.GetX()+2,p.GetY());
			else if(wParam == 'W')
				p.SetPos(p.GetX(),p.GetY()-2);
			else if(wParam == 'S')
				p.SetPos(p.GetX(),p.GetY()+2);

			break;
		}

return DefWindowProc(hWnd, msg, wParam, lParam);
}
