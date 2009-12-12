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

DirectXInterface::DirectXInterface()
{
	hwnd = NULL;
	pD3D = NULL;
	pD3DDevice = NULL;
}

DirectXInterface::~DirectXInterface()
{
	if(hwnd)
		UnregisterClass("WoA",hInstance);		// Unregister our window's class //
}

bool DirectXInterface::CreateAppWindow()
{
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

	// Create the application's window //
	if((hwnd = CreateWindow("WoA", "woa",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,0,0,1024,768,HWND_DESKTOP,NULL,hInstance,NULL)) == NULL)
		return false;

return true;
}

void DirectXInterface::MessagePump()
{
	MSG msg;
	if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
}

HRESULT DirectXInterface::Initialize(HINSTANCE hInstance,bool Windowed)
{
	this->hInstance = hInstance;
	if(!CreateAppWindow())			// Create the apps window
		return E_FAIL;
	
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

	pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	ViewWidth = d3dpp.BackBufferWidth;
	ViewHeight = d3dpp.BackBufferHeight-100;		// Space for the HUD //
	D3DXCreateSprite(pD3DDevice,&pSprite);

	sDrawMgr->Setup(pD3DDevice,pSprite,ViewWidth,ViewHeight);
	sWorldView->Setup(pD3DDevice,pSprite);
	sHudView->Setup(pD3DDevice,pSprite);
	sScreenLog->Setup(pD3DDevice);

return S_OK;
}

void DirectXInterface::Cleanup()
{
	delete sHudView;
	delete sDrawMgr;
	delete sWorldView;
	delete sScreenLog;

	SAFE_RELEASE(pSprite);
	SAFE_RELEASE(pD3DDevice);
	SAFE_RELEASE(pD3D);
}

void DirectXInterface::BeginScene()
{
	MessagePump();		// Dont know where to put this :< //
	if(pD3DDevice == NULL)
		return;
	pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_COLORVALUE(0.35f,0.53f,0.7f,1.0f),1.0f,0);	// If covering the whoe screen with pictures its not necceseary (not sure) ^^ //
	pD3DDevice->BeginScene();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void DirectXInterface::EndScene()
{
	if(pD3DDevice == NULL)
		return;

	sScreenLog->Draw();
	pSprite->End();
	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL,NULL,NULL,NULL);		// TODO: check present paramters maybe there is a better on than just NULL-s //
}
