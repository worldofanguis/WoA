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

#define KEY_DOWN(key)		(Keys[key] & 0x80)
#define KEY_UP(key)			(!(Keys[key] & 0x80))
#define KEY_PRESSED(key)	((Keys[key] & 0x80) && !PrevKeys[key])
#define KEY_RELEASED(key)	(!Keys[key] && (PrevKeys[key] & 0x80))


class KeyboardController
{
protected:
	BYTE Keys[256];				// The keyboard state //
	BYTE PrevKeys[256];
	
	KeyboardController();
	virtual ~KeyboardController() {Release();}
	
	void ReadKeyboard();
private:	
	void Release();
	void InitController();
	
	static IDirectInput8* DXInput;
	static IDirectInputDevice8* DXKeyboardDevice;
};