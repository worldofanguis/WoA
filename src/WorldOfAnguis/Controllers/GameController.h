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


/* Class: GameController
 * Description: This class is dedicated to handle all 'ingame' events
 *				like initializing the world, players
 *				reading the keyboard, moving the camera, etc.
 *				So its the main loop of the program while 'ingame'.
 *
 * Functions: The only public function is the constructor,
 *			  so all we have to do is creating the object if we want to start he game
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
	
private:
	void Run();
	void Render(DWORD diff);

	void FollowUnit(Unit *unit);			// Follows the specified unit with the camera //

	int ViewWidth;			// Screen width (BackBuffer width) //
	int ViewHeight;			// Screen height (BackBuffer height) //
	int ViewLeft;			// Left coord of the screen //
	int ViewTop;			// Top coord of the screen //

};