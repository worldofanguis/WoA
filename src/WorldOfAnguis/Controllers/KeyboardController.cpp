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


#include "KeyboardController.h"
#include "Graphics/DirectX/DirectXInterface.h"


IDirectInputDevice8* KeyboardController::DXKeyboardDevice = NULL;
IDirectInput8* KeyboardController::DXInput = NULL;

KeyboardController::KeyboardController()
{
	ZeroMemory(Keys,256);
}

void KeyboardController::InitController()
{
	DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&DXInput,NULL);
	DXInput->CreateDevice(GUID_SysKeyboard,&DXKeyboardDevice, NULL);
	DXKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	DXKeyboardDevice->SetCooperativeLevel(sDXInterface->GetHwnd(),DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void KeyboardController::ReadKeyboard()
{
	if(DXKeyboardDevice == NULL)
		InitController();
		
	DXKeyboardDevice->Acquire();

	memcpy(PrevKeys,Keys,256);
	ZeroMemory(Keys,sizeof(Keys));
	DXKeyboardDevice->GetDeviceState(sizeof(Keys),Keys);
}

void KeyboardController::Release()
{
	if(DXKeyboardDevice)
		{
		DXKeyboardDevice->Unacquire();
		DXKeyboardDevice->Release();
		DXKeyboardDevice = NULL;
		}

	SAFE_RELEASE(DXInput);
}
