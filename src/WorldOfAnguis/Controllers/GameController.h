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
#include "KeyboardController.h"
#include "Units/Player/Player.h"


class GameController : KeyboardController
{
public:
	GameController();
	~GameController();
	
	void Run();
private:
	void Render(DWORD diff);
	
	
	void SetView(int Left,int Top) {ViewLeft = Left;ViewTop = Top;}		// Set the viewpoint //
	void ScrollLeft(int Dist);			// Scrolling the screen left with dist //
	void ScrollRight(int Dist);			// Scrolling the screen right with dist //
	void ScrollUp(int Dist);			// Scrolling the screen up with dist //
	void ScrollDown(int Dist);			// Scrolling the screen down with dist //
	void FollowPlayer(Player * p);

	int ViewWidth;			// Screen width (BackBuffer width) //
	int ViewHeight;			// Screen height (BackBuffer height) //
	int ViewLeft;			// Left coord of the screen //
	int ViewTop;			// Top coord of the screen //

};