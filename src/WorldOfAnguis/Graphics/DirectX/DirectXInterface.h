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
#include "Units/Player/Player.h"
#include "World/World.h"
#include "Units/Player/HUD.h"

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
	/* Registers a unit (Player,Missile,etc...) for drawing */
	static void RegisterUnit(Unit* unit) {Objects.push_back(unit);}
	/* UnRegisters a unit (because its expired) */
	static void UnRegisterUnit(Unit* unit) {for(it=Objects.begin();it!=Objects.end();it++){if((*it) == unit){Objects.erase(it); break;}}}
	
private:
	/* Check if the unit is in the field of view */
	bool InSight(Unit* unit);

	static World* world;						// world pointer //
	static HUD* hud;							// hud pointer //
	static std::vector<Unit*> Objects;			// containter for the units //
	static std::vector<Unit*>::iterator it;		// iterator for the units //
	
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
