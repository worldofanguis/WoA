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
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

#include "Graphics\DirectX\DirectXInterface.h"


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
	
	ShowFPS = true;
}

DirectXInterface::~DirectXInterface()
{
	Cleanup();
}

HRESULT DirectXInterface::Initialize(HWND hwnd,bool Windowed)
{
	// Create the D3D object, which is needed to create the D3DDevice. //
	if((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return E_FAIL;

	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp; 
	
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if(Windowed)
		{
		// Get the current desktop display mode //
		if(FAILED( pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
			return E_FAIL;

		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = d3ddm.Format;				// D3DFMT_X8R8G8B8 !!! // 
		d3dpp.Flags = D3DPRESENT_INTERVAL_ONE;				// D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	// D3DPRESENT_INTERVAL_IMMEDIATE // We want to be able to directly write to backbuffer memory
		}
	else
		{
		d3dpp.Windowed               = FALSE;
		d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferWidth        = 1024;
		d3dpp.BackBufferHeight       = 768;
		d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
		d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;		// This is what we need ? //
		
		ShowCursor(false);		 		// Hide cursor //
		}

	// Create D3D Device //
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&pD3DDevice)))
        return E_FAIL;

	if(FAILED(pD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer)))
		return E_FAIL;

	D3DXCreateFont(pD3DDevice,21,0,FW_BOLD,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Arial",&pFont);
 

	ViewWidth = d3dpp.BackBufferWidth;
	ViewHeight = d3dpp.BackBufferHeight;
	D3DXCreateSprite(pD3DDevice,&pSprite);
	
	/* Set the static parts of the View classes */
	DXWorldView::SetDevice(pD3DDevice);
	DXWorldView::SetBackBuffer(pBackBuffer);
	
	DXPlayerView::SetDevice(pD3DDevice);
	DXPlayerView::SetSprite(pSprite);
return S_OK;
}

void DirectXInterface::Cleanup()
{
//	SAFE_RELEASE(pBackBuffer);			// We havent created the backbuffer just used it, so i think we dont need to realease it (or do we ?) //
	SAFE_RELEASE(pFont);
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
	
	// Drawing the world //
	if(world)
		world->Draw(ViewLeft,ViewTop,ViewWidth,ViewHeight);

	
	// Drawing objects: Players, Pickups, Bullets, etc (everything what implements <Units> can be added the the drawing queue) //
	for(it=Objects.begin();it!=Objects.end();it++)
		{
		(*it)->Update();		// Updating the game objects (should be moved from there) since we are responsible for DRAWING only //
		if(InSight((*it)))
			(*it)->Draw(ViewLeft,ViewTop);
		}

	// Display FPS counter //
	if(ShowFPS)
		{
		if(PrevTickCount != TickCount)
			{
			sprintf_s(FPS,sizeof(FPS),"%d",1000/(TickCount-PrevTickCount));
			pFont->DrawText(NULL,FPS,-1,NULL,DT_LEFT|DT_NOCLIP,0xFF0000FF);
			}
		}

	pSprite->End();
	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL,NULL,NULL,NULL);		// TODO: check present paramters maybe there is a better on than just NULL-s //
	PrevTickCount = TickCount;
	TickCount = GetTickCount();
}

bool DirectXInterface::InSight(Unit* unit)
{
	/* Check if the object we want to draw is truly in sight (if not just leave it alone) */
	if((ViewLeft < (unit->GetX()+unit->GetWidth())) && (ViewTop < (unit->GetY()+unit->GetHeight())) &&
	   ((ViewLeft+ViewWidth) > unit->GetX()) && ((ViewTop+ViewHeight) > unit->GetY()))
		return true;
return false;
}

/* Maybe this functions should be moved to 2 (ScrollingVertical and ScrollingHorizontal) */
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

