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
#include "Graphics/DirectX/DirectXInterface.h"

World::World()
{
	Map = NULL;
	DirectXInterface::RegisterWorld(this);
}

World::~World()
{
	delete[] Map;
	DirectXInterface::UnRegisterWorld();
}

void World::LoadMaps(char *HitMap,char* TexturedMap)
{
	DXWorldView::LoadWorldTexture(TexturedMap);
	
	/* Later we wont need these */
	Width = DXWorldView::GetSurfaceWidth();
	Height = DXWorldView::GetSurfaceHeight();
}
