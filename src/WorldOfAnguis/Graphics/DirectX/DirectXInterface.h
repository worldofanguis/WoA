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
 
 
#pragma once
#include "Common.h"
#include "Singleton.h"
#include "Graphics/DirectX/DrawMgr.h"
#include "Graphics/DirectX/World/DXWorldView.h"
#include "Graphics/DirectX/HUD/DXHUDView.h"

class DirectXInterface : public Singleton<DirectXInterface>
{
public:
	DirectXInterface();
	~DirectXInterface();
	
	HRESULT Initialize(HINSTANCE hInstance,bool Windowed);			// Initializes DirectX //
	void Cleanup();								// Cleanup DirectX //
	
	HINSTANCE GetInstance() {return hInstance;}
	HWND GetHwnd() {return hwnd;}
	
	void Render();						// Render the screen //
	
	void SetView(int Left,int Top) {ViewLeft = Left;ViewTop = Top;}		// Set the viewpoint //
	void ScrollLeft(int Dist);			// Scrolling the screen left with dist //
	void ScrollRight(int Dist);			// Scrolling the screen right with dist //
	void ScrollUp(int Dist);			// Scrolling the screen up with dist //
	void ScrollDown(int Dist);			// Scrolling the screen down with dist //
	
private:
	bool CreateAppWindow();
	void MessagePump();

	HWND hwnd;							// Window handle //
	HINSTANCE hInstance;				// Window instance //
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;		// D3DX Device //
	LPD3DXSPRITE pSprite;				// Sprite for drawing images //
	
	int ViewWidth;			// Screen width (BackBuffer width) //
	int ViewHeight;			// Screen height (BackBuffer height) //
	int ViewLeft;			// Left coord of the screen //
	int ViewTop;			// Top coord of the screen //
	
	LPD3DXFONT pFont;		// Font for drawing FPS //
	bool ShowFPS;
	char FPS[10];
	DWORD TickCount,PrevTickCount;
	
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {return DefWindowProc(hWnd,msg,wParam,lParam);}		// We dont want to do anything with window messages :< //
};

#define sDXInterface DirectXInterface::Instance()