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


/* Class: KeyboardController
 * Description: The only purpose of this class is handling the keyboard,
 *				if we want to use it we have to inherit it.
 *
 * Functions: ReadKeyboard()
 *				this function reads in the keystates, so we have to call it in every loop once
 */


#pragma once

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "Common.h"

/* Keystate macros */
#define KEY_DOWN(key)		(Keys[key] & 0x80)
#define KEY_UP(key)			(!(Keys[key] & 0x80))
#define KEY_PRESSED(key)	((Keys[key] & 0x80) && !PrevKeys[key])
#define KEY_RELEASED(key)	(!Keys[key] && (PrevKeys[key] & 0x80))


class KeyboardController
{
protected:
	KeyboardController();
	virtual ~KeyboardController() {Release();}
	
	void ReadKeyboard();

	BYTE Keys[256];				// The keyboard state //
	BYTE PrevKeys[256];
private:	
	void Release();
	void InitController();
	
	static IDirectInput8* DXInput;						// DirectX input device //
	static IDirectInputDevice8* DXKeyboardDevice;		// DirectX keyboard device //
};