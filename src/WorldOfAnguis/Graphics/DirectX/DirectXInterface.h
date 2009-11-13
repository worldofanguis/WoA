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
#include "World/World.h"
#include "Units/Player/HUD.h"

#include "Graphics/DirectX/Units/DrawMgr.h"

class DirectXInterface
{
public:
	DirectXInterface();
	~DirectXInterface();
	
	HRESULT Initialize(HWND hwnd,bool Windowed);		// Initializes DirectX //
	void Cleanup();								// Cleanup DirectX //
	
	void Render();						// Render the screen //
	
	void SetView(int Left,int Top) {ViewLeft = Left;ViewTop = Top;}		// Set the viewpoint //
	void ScrollLeft(int Dist);			// Scrolling the screen left with dist //
	void ScrollRight(int Dist);			// Scrolling the screen right with dist //
	void ScrollUp(int Dist);			// Scrolling the screen up with dist //
	void ScrollDown(int Dist);			// Scrolling the screen down with dist //
	
	/* Registers the world class for drawing the world */
	static void RegisterWorld(World* world) {DirectXInterface::world = world;}
	/* UnRegisters the world */
	static void UnRegisterWorld() {DirectXInterface::world = NULL;}
	/* Registers the hud class for drawing the hud */
	static void RegisterHUD(HUD* hud) {DirectXInterface::hud = hud;}
	/* UnRegisters the world */
	static void UnRegisterHUD() {DirectXInterface::hud = NULL;}	
private:
	static World* world;						// world pointer //
	static HUD* hud;							// hud pointer //
	
	DrawMgr* drawmgr;
	HWND hwnd;							// Window handle //
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
};
