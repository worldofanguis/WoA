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
 
#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9.lib")		// d3dx9d.lib is the debug lib, just the dll is missing ?_? //
#else
#pragma comment(lib, "d3dx9.lib")
#endif

#include "Graphics\DirectX\DirectXInterface.h"

/* Static parts */
World* DirectXInterface::world = NULL;
std::vector<Unit*> DirectXInterface::Objects;
std::vector<Unit*>::iterator DirectXInterface::it;

DirectXInterface::DirectXInterface()
{
	pD3D = NULL;
	pD3DDevice = NULL;
	pBackBuffer = NULL;
	
	world = NULL;
	Objects.clear();
}

DirectXInterface::~DirectXInterface()
{
	Cleanup();
}

HRESULT DirectXInterface::Initialize(HWND hwnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return E_FAIL;

	// Get the current desktop display mode
	D3DDISPLAYMODE d3ddm;
	if(FAILED( pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;				// D3DFMT_X8R8G8B8 !!! // 
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	// We want to be able to directly write to backbuffer memory

	// Create D3D Device
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp, &pD3DDevice)))
        return E_FAIL;

	if(FAILED(pD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer)))
		return E_FAIL;

	ViewWidth = d3dpp.BackBufferWidth;
	ViewHeight = d3dpp.BackBufferHeight;
	D3DXCreateSprite(pD3DDevice,&pSprite);
	
	DXWorldView::SetDevice(pD3DDevice);
	DXWorldView::SetBackBuffer(pBackBuffer);
	
	DXPlayerView::SetDevice(pD3DDevice);
	DXPlayerView::SetSprite(pSprite);
return S_OK;
}

void DirectXInterface::Cleanup()
{
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pD3DDevice);
	SAFE_RELEASE(pD3D);
}

void DirectXInterface::Render()
{
	if(pD3DDevice == NULL)
		return;
		
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0),1.0f,0);	// If covering the whoe screen with pictures its not necceseary (not sure) ^^ //
	pD3DDevice->BeginScene();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	// Drawing World //
	if(world)
		world->Draw(ViewLeft,ViewTop,ViewWidth,ViewHeight);
	// End Drawind World //
	
	// Drawing Objects: Players, Bullets, etc //
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		(*it)->Update();		// Updating the game objects //
		if(InSight((*it)))
			(*it)->Draw(ViewLeft,ViewTop);
		}
	// End Drawing Objects //
	pSprite->End();
	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL,NULL,NULL,NULL);
}

bool DirectXInterface::InSight(Unit* unit)
{
	if((ViewLeft < (unit->GetX()+unit->GetWidth())) && (ViewTop < (unit->GetY()+unit->GetHeight())) &&
	   ((ViewLeft+ViewWidth) > unit->GetX()) && ((ViewTop+ViewHeight) > unit->GetY()))
		return true;
return false;
}

void DirectXInterface::ScrollLeft(int Dist)
{
	if(ViewLeft-Dist > 0)
		ViewLeft -= Dist;
	else
		ViewLeft = 0;
}

void DirectXInterface::ScrollRight(int Dist)
{
	if(ViewLeft+ViewWidth+Dist < world->GetWidth())
		ViewLeft += Dist;
	else
		ViewLeft = world->GetWidth()-ViewWidth;
}

void DirectXInterface::ScrollUp(int Dist)
{
	if(ViewTop-Dist > 0)
		ViewTop -= Dist;
	else
		ViewTop = 0;
}

void DirectXInterface::ScrollDown(int Dist)
{
	if(ViewTop+ViewHeight+Dist < world->GetHeight())
		ViewTop += Dist;
	else
		ViewTop = world->GetHeight()-ViewHeight;
}

