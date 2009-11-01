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


#include "Unit.h"

Unit::Unit()
{
	X = Y = 0;
	vX = vY = 0;
	aX = aY = 0;

	Width = Height = 0;
}

Unit::~Unit()
{
}

bool Unit::HitTest()
{
return false;
}
