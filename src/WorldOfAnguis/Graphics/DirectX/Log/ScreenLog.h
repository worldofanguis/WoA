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