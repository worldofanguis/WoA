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

IDirectInputDevice8* KeyboardController::DXKeyboardDevice = NULL;
IDirectInput8* KeyboardController::DXInput = NULL;

void KeyboardController::InitController()
{
	DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&DXInput,NULL);
	DXInput->CreateDevice(GUID_SysKeyboard,&DXKeyboardDevice, NULL);
	DXKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	DXKeyboardDevice->SetCooperativeLevel(/*HWND*/NULL,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void KeyboardController::ReadKeyboard()
{
	if(DXKeyboardDevice == NULL)
		InitController();
		
	DXKeyboardDevice->Acquire();
	
	ZeroMemory(Keys,sizeof(Keys));
	DXKeyboardDevice->GetDeviceState(sizeof(Keys),Keys);
}

void KeyboardController::Release()
{
	if(DXKeyboardDevice)
		{
		DXKeyboardDevice->Unacquire();
		DXKeyboardDevice->Release();
		}

	SAFE_RELEASE(DXInput);
}
