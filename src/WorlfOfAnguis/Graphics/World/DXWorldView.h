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
 
 // View for the world class -> this class is responsigble for drawing the map on the screen //
 
 #include "Common.h"

class DXWorldView
{
public:
	static void SetDevice(LPDIRECT3DDEVICE9 pDevice) {DXWorldView::pDevice = pDevice;}
	static void SetSurface(LPDIRECT3DSURFACE9 pSurface) {DXWorldView::pSurface = pSurface;}

protected:
	DXWorldView();
	~DXWorldView();
	void Draw(int Left,int Top,int Width,int Height);
	
	static LPDIRECT3DDEVICE9 pDevice;
	static LPDIRECT3DSURFACE9 pSurface;

};