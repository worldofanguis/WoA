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
 

/* Class: DirectXInterface
 * Description: Doing all the drawing stuff, creating the window, the directx devices for drawing
 *				initializing the Draw classes with the resolution and the used devices
 *
 * Functions: Initialize(...)
 *				create the drawing resources
 *			  Cleanup()
 *				free the resources
 *			  BeginScene()
 *				initialize the drawing - should be called before we tell the Draw classes to do the drawing
 *			  EndScene()
 *				display the screen buffer
 */
 
 
#pragma once
#include "Common.h"
#include "Singleton.h"
#include "Graphics/DirectX/DrawMgr.h"
#include "Graphics/DirectX/World/DXWorldView.h"
#include "Graphics/DirectX/HUD/DXHUDView.h"
#include "Graphics/DirectX/Log/ScreenLog.h"

class DirectXInterface : public Singleton<DirectXInterface>
{
public:
	DirectXInterface();
	~DirectXInterface();
	
	HRESULT Initialize(HINSTANCE hInstance,bool Windowed,bool EnableVSync = false);			// Initializes DirectX //
	void Cleanup();													// Cleanup DirectX //
	
	HINSTANCE GetInstance() {return hInstance;}
	HWND GetHwnd() {return hwnd;}
	LPDIRECT3DDEVICE9 GetDevice() {return pD3DDevice;}
	LPD3DXSPRITE GetSprite() {return pSprite;}
	
	int GetViewWidth() {return ViewWidth;}
	int GetViewHeight() {return ViewHeight;}
	
	void BeginScene();
	void EndScene();	
private:
	bool CreateAppWindow();
	void MessagePump();

	HWND hwnd;							// Window handle //
	HINSTANCE hInstance;				// Window instance //
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;		// D3DX Device //
	LPD3DXSPRITE pSprite;				// Sprite for drawing images //

	int ViewWidth,ViewHeight;
	
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
		if(msg == WM_SYSCOMMAND)
			{
			if(wParam == SC_CLOSE)
				{
				DirectXInterface::Instance()->Cleanup();
				exit(0);
				return 0;
				}
			}
		return DefWindowProc(hWnd,msg,wParam,lParam);
		}		// We dont want to do anything with window messages :< //
};

#define sDXInterface DirectXInterface::Instance()