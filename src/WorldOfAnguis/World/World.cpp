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
#include "Units/Explosion/Explosion.h"

World::World()
{
	Map = NULL;
	PPHM = 1;				// PixelPerHitMap (2 means 2x2 pixel is 1 entry in the hit map) // dont think we should go higher than 2 //
}

World::~World()
{
	delete[] Map;
}

/* NOTE: Not working with maps which are not divisible with PPHM! << only for 24bit BMP-s >>
 *  TODO: Fix this (but its not that important)
 */
bool World::LoadMap(char *MapName)
{
	FILE *FKez;
	char FileName[MAX_PATH];
	sprintf_s(FileName,sizeof(FileName),"%s.bmp",MapName);
	
	fopen_s(&FKez,FileName,"rb");
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
			else
				Map[(Height-1-h)*Width+w] = 0;
			fseek(FKez,(PPHM-1)*3,SEEK_CUR);		// Move the file pointer with PPHM-1 pixels //
			}
		fseek(FKez,LinePadding,SEEK_CUR);										// Skip the line padding //			
		fseek(FKez,((PPHM-1)*bmih.biWidth*3)+((PPHM-1)*LinePadding),SEEK_CUR);		// Skip PPHM-1 lines + padding //
		}
	fclose(FKez);

	/* Load the TexturedMap */
	sprintf_s(FileName,sizeof(FileName),"%sTextured.bmp",MapName);
	if(!sWorldView->LoadWorldTexture(FileName))
		return false;

	// Update our display surface //
	sWorldView->UpdateSurface(Map,Width,PPHM,NULL);
return true;
}

void World::Explode(Unit* explosion)
{
 	Explosion* e = (Explosion*)explosion;
	char* emap = e->GetExplosionMap();
	int R = 2*e->GetRadius();
	int X= e->GetX();
	int Y= e->GetY();

	int MapAddr;

	for(int i=0; i<R;i++)			// Iterators for the ExplosionMap
		for(int j=0; j<R;j++)
			{
			MapAddr = (Y/PPHM+i)*Width+(X/PPHM+j);		// just to avoid calculating this address 4times / cycle

			if(MapAddr < 0 || MapAddr > MapSize)
				continue;

			if(emap[i*R+j])
				if(Map[MapAddr] == 1)
					Map[MapAddr] = 0;
			}

	RECT DirtyRegion = {X,Y,X+(R*PPHM),Y+(R*PPHM)};
	sWorldView->UpdateSurface(Map,Width,PPHM,&DirtyRegion);
}

void World::PrintMap()
{
	FILE* f = fopen("Map.txt", "w");

	for(int i=0;i<Height;i++)
		{
		for(int j=0;j<Width;j++)
			fprintf(f,"%d",Map[i*Width+j]);
		fprintf(f,"\n");
		}
	fclose(f);
}