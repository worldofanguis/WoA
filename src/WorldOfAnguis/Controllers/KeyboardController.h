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

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "Common.h"

#define KEY_DOWN(key) (Keys[key] & 0x80)


class KeyboardController
{
public:
	static void Release();
protected:
	BYTE Keys[256];				// The keyboard state //
	
	KeyboardController() {}
	virtual ~KeyboardController() {}
	
	void ReadKeyboard();
private:	
	void InitController();
	
	static IDirectInput8* DXInput;
	static IDirectInputDevice8* DXKeyboardDevice;
};