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
 
 // Interface for drawing on the screen //
 
#pragma once
#include "Common.h"
#include "Units/Player/Player.h"
#include "World/World.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

class DirectXInterface
{
public:
	DirectXInterface();
	~DirectXInterface();
	
	HRESULT Initialize(HWND hwnd);		// Initializes DirectX //
	void Cleanup();						// Cleanup DirectX //
	
	void Render();						// Render the screen, (units->update()) should be moved from here ? //
	
	void SetSize(int Width,int Height) {ViewWidth = Width; ViewHeight = Height;}		// Set the screen size (later it should be automatic) //
	void SetView(int Left,int Top) {ViewLeft = Left;ViewTop = Top;}		// Set the viewpoint //
	void ScrollLeft(int Dist);			// Scrolling the screen left with dist //
	void ScrollRight(int Dist);			// Scrolling the screen right with dist //
	void ScrollUp(int Dist);			// Scrolling the screen up with dist //
	void ScrollDown(int Dist);			// Scrolling the screen down with dist //
	
	/* Registers the world class for drawing the world */
	void RegisterWorld(World* world) {this->world = world;}
	/* Registers a unit (Player,Missile,etc...) for drawing */
	void RegisterUnit(Unit* unit) {Objects.push_back(unit);}
	/* UnRegisters a unit (because its expired) */
	void UnRegisterUnit(Unit* unit) {for(it=Objects.begin();it!=Objects.end();it++){if((*it) == unit){Objects.erase(it); break;}}}
	
private:
	/* Check if the unit is in the field of view */
	bool InSight(Unit* unit);

	World* world;						// world pointer //
	std::vector<Unit*> Objects;			// containter for the units //
	std::vector<Unit*>::iterator it;
	
	HWND hwnd;							// Window handle //
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;		// D3DX Device //
	LPDIRECT3DSURFACE9 pBackBuffer;		// Surface for drawing the map //
	LPD3DXSPRITE pSprite;				// Sprite for drawing images //
	
	int ViewWidth;			// Screen width //
	int ViewHeight;			// Screen height //
	int ViewLeft;			// Left coord of the screen //
	int ViewTop;			// Top coord of the screen //

};
