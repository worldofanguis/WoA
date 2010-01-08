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
#include "Units/Unit.h"

class GameController : KeyboardController
{
public:
	GameController();
	~GameController();
	
	void Run();
private:
	void Render(DWORD diff);

	void SetView(int Left,int Top) {ViewLeft = Left;ViewTop = Top;}		// Set the viewpoint //

	void FollowUnit(Unit *unit);			// Follows the specified unit with the camera //

	int ViewWidth;			// Screen width (BackBuffer width) //
	int ViewHeight;			// Screen height (BackBuffer height) //
	int ViewLeft;			// Left coord of the screen //
	int ViewTop;			// Top coord of the screen //

};