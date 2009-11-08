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
#include "Units/Unit.h"

World::World()
{
	Map = NULL;
	PPHM = 2;				// PixelPerHitMap (2 means 2x2 pixel is 1 entry in the hit map) // dont think we should go higher than 2 //
	DirectXInterface::RegisterWorld(this);			// Register the world pointer in the DXInterface class //
	Unit::RegisterWorld(this);					// Register the world pointer in the Unit class //
}

World::~World()
{
	delete[] Map;
	DirectXInterface::UnRegisterWorld();
	Unit::UnRegisterWorld();
}

/* NOTE: Not working with maps which are not divisible with PPHM! << only for 24bit BMP-s >>
 *  TODO: Fix this (but its not that important)
 */
bool World::LoadMaps(char *HitMap,char* TexturedMap)
{
	FILE *FKez;
	fopen_s(&FKez,HitMap,"rb");
	if(FKez == NULL)
		return false;

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	fread(&bmfh,sizeof(BITMAPFILEHEADER),1,FKez);
	if(bmfh.bfType != 0x4D42)		// check if its a BMP (BM flag) //
		{
		fclose(FKez);
		return false;
		}

	fread(&bmih,sizeof(BITMAPINFOHEADER),1,FKez);
	
	Width = bmih.biWidth/PPHM;
	Height = bmih.biHeight/PPHM;
	int LinePadding = ((bmih.biSizeImage)-(bmih.biWidth*bmih.biHeight*3))/bmih.biHeight;		// Calc the line padding //
	
	MapSize = Width*Height;
	Map = new char[MapSize];
	ZeroMemory(Map,MapSize);

	fseek(FKez,bmfh.bfOffBits,SEEK_SET);
	DWORD PixelColor = 0;
	
	/* NOTE: Windows BMP is stored in a reversed format, so it starts with the LAST line
	 *       To every line is added a padding for 4 byte alignment (1,2 or 3 bytes)
	 */
	for(int h=0;h<Height;h++)
		{
		for(int w=0;w<Width;w++)
			{
			fread(&PixelColor,3,1,FKez);				// Read 1 Pixel //
			if(PixelColor == 0xFF0000)						// RED //
				Map[(Height-1-h)*Width+w] = 1;					// Destructable earth //
			else if(PixelColor == 0x00FF00)					// GREEN //
				Map[(Height-1-h)*Width+w] = 2;					// Undestructable earth //
			else if(PixelColor == 0x0000FF)					// BLUE //
				Map[(Height-1-h)*Width+w] = 3;					// ?_? //
			else if(PixelColor == 0xFFFFFF)
				Map[(Height-1-h)*Width+w] = 0;
			else
				Map[(Height-1-h)*Width+w] = 9;
			fseek(FKez,(PPHM-1)*3,SEEK_CUR);		// Move the file pointer with PPHM-1 pixels //
			}
		fseek(FKez,LinePadding,SEEK_CUR);										// Skip the line padding //			
		fseek(FKez,((PPHM-1)*bmih.biWidth*3)+((PPHM-1)*LinePadding),SEEK_CUR);		// Skip PPHM-1 lines + padding //
		}
	fclose(FKez);

	/* Load the TexturedMap */
	if(!DXWorldView::LoadWorldTexture(TexturedMap))
		return false;

	// Update our display surface //
	DXWorldView::UpdateSurface(Map,Width,PPHM);
return true;
}

void World::Explode(Explosion* Ex)
{
	// Deformation //

	DXWorldView::UpdateSurface(Map,Width,PPHM);
}

