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
	PPHM = 1;
	DirectXInterface::RegisterWorld(this);			// could be moved to the DXWorldView //
}

World::~World()
{
	delete[] Map;
	DirectXInterface::UnRegisterWorld();
}

/* TODO: FIX ME!!! */
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
	
	MapSize = Width*Height;
	Map = new char[MapSize];
	ZeroMemory(Map,MapSize);

	fseek(FKez,bmfh.bfOffBits,SEEK_SET);
	DWORD PixelColor = 0;
	for(int i=0;i<MapSize;i++)
		{
		fread(&PixelColor,3,1,FKez);			// Read 1 Pixel //
		if(PixelColor == 0xFF0000)						// RED //
			Map[i] = 1;										// Destructable earth //
		else if(PixelColor == 0x00FF00)					// GREEN //
			Map[i] = 2;										// Undestructable earth //
		else if(PixelColor == 0x0000FF)					// BLUE //
			Map[i] = 3;										// ?_? //
		else if(PixelColor == 0xFFFFFF)
			Map[i] = 0;
		else
			Map[i] = 9;
//		fseek(FKez,(PPHM-1)*3,SEEK_CUR);		// Move the file pointer with PPHM-1 pixels //
		if((i % Width == 0) && i)					// We have read a whole line //
			{
			fseek(FKez,((bmih.biSizeImage)-(bmih.biWidth*bmih.biHeight*3))/bmih.biHeight,SEEK_CUR);				// Skip the line padding //			
//			fseek(FKez,((PPHM-1)*Width)+(PPHM-1)*((bmih.biSizeImage/(bmih.biWidth*3))/bmih.biHeight),SEEK_CUR);		// Skip PPHM-1 lines + padding //
			}
		}
	fclose(FKez);
	/* Load the TexturedMap */
	if(!DXWorldView::LoadWorldTexture(TexturedMap))
		return false;
	
	/* DEBUG ONLY */
	FKez = fopen("Map.txt","w");
	for(int h=0;h<Height;h++)
		{
		for(int w=0;w<Width;w++)
			{
			fprintf(FKez,"%d",Map[(h*Width)+w]);
			}
		fprintf(FKez,"\n");
		fflush(FKez);
		}
	fclose(FKez);
	exit(0);
	/* END */
	// Update our display surface //
	DXWorldView::UpdateSurface(Map,Width,PPHM);
return true;
}

void World::Explode(Explosion* Ex)
{
	// Deformation //

	DXWorldView::UpdateSurface(Map,Width,PPHM);
}

