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
 

#include "World.h"

World::World()
{
	Map = NULL;
}

World::~World()
{
	delete[] Map;
}

void World::LoadMaps(char *HitMap,char* TexturedMap)
{
	DXWorldView::LoadWorldTexture(TexturedMap);
}
