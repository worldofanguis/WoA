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


/* Class: ScreenLog
 * Description: With this class we can draw the value of many variables
 *				on the screen with a specified color and location
 *
 * Functions: Setup(...)
 *				setup the class with the drawing devices
 *			  AddTrack(...)
 *				we can add a variable to the tracklist to make it shown on every frame
 *				NOTE1: we can use this only for variables that are on a fixed location in the memory
 *				NOTE2: this function should be called only once (not in every frame)
 *			  DrawNow(...)
 *				draw a variable on the screen without the tracklist
 *				NOTE1: this function can be used for variables that may change its location in the memory
 *				NOTE2: this call must be placed after the DXI->BeginScene() call
 *			  Draw()
 *				draws the variables which are on the tracklist, this function is called from the DXI->EndScene()
 */


#pragma once
#include "Common.h"
#include "Singleton.h"

class ScreenLog : public Singleton<ScreenLog>
{
public:
	ScreenLog();
	~ScreenLog();

	/* Struct for holding the informations */
	struct Track
	{
		enum TYPES {TEXT,CHAR,BOOL,FLOAT,INT,UINT};		// Types we can track - Use: ScreenLog::Track::<TYPE> //

		Track(void* data,TYPES type,int x,int y,COLORREF color)
		{
			Data = data;
			Type = type;
			Pos.left = x;
			Pos.top = y;
			Color = color;
		}
		
		void* Data;			// Pointer to the <memory location> of the variable we want to draw //
		TYPES Type;
		RECT Pos;
		COLORREF Color;
	};
	
	/* Requies the D3DDevice to create the Font object */
	void Setup(LPDIRECT3DDEVICE9 pDevice);

	/* Setup a tracking for a variable
	 * NOTE: Call this only ONCE for every variable, so NOT in every frame
	 *		 Can be used only on variables which wont be destroyed, because it saves only the MEMORY LOCATION of the variable
	 */
	void AddTrack(void* Data,Track::TYPES Type,int X,int Y,COLORREF Color);

	/* Draw the variable on the screen
	 * NOTE: Must be called after the BeginScence (and in every frame)
	 */
	void DrawNow(void* Data,Track::TYPES Type,int X,int Y,COLORREF Color);

	/* This function is called in the EndScene function, so we DONT use it */
	void Draw();
private:
	Track* Current;
	char Text[256];
	std::vector<Track*> Tracker;
	std::vector<Track*>::iterator it;
	
	LPD3DXFONT pFont;
};

#define sScreenLog ScreenLog::Instance()