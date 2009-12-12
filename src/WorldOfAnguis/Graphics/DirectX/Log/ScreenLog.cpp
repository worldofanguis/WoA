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


#include "ScreenLog.h"

ScreenLog::ScreenLog()
{
	Tracker.clear();
	pFont = NULL;
}

ScreenLog::~ScreenLog()
{
	SAFE_RELEASE(pFont);
	
	for(it=Tracker.begin();it!=Tracker.end();it++)
		delete *it;

	Tracker.clear();
}

void ScreenLog::Setup(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(pDevice,21,0,FW_BOLD,1,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Arial",&pFont);
}

void ScreenLog::Draw()
{
	for(it=Tracker.begin();it!=Tracker.end();it++)
		{
		Current = *it;
		switch(Current->Type)
			{
			case Track::CHAR:
				sprintf_s(Text,sizeof(Text),"%c",*(char*)Current->Data);
				break;
			case Track::TEXT:
				sprintf_s(Text,sizeof(Text),"%s",*(char*)Current->Data);
				break;
			case Track::FLOAT:
				sprintf_s(Text,sizeof(Text),"%f",*(float*)Current->Data);
				break;
			case Track::INT:
				sprintf_s(Text,sizeof(Text),"%d",*(int*)Current->Data);
				break;
			case Track::UINT:
				sprintf_s(Text,sizeof(Text),"%u",*(DWORD*)Current->Data);
				break;
			default:
				sprintf_s(Text,sizeof(Text),"Unknown");
			}
		pFont->DrawText(NULL,Text,-1,&Current->Pos,DT_LEFT|DT_NOCLIP,Current->Color);
		}
}

void ScreenLog::AddTrack(void* Data,Track::TYPES Type,int X,int Y,COLORREF Color)
{
	Tracker.push_back(new Track(Data,Type,X,Y,Color));
}

void ScreenLog::DrawNow(void* Data,Track::TYPES Type,int X,int Y,COLORREF Color)
{
	switch(Type)
		{
		case Track::CHAR:
			sprintf_s(Text,sizeof(Text),"%c",*(char*)Data);
			break;
		case Track::TEXT:
			sprintf_s(Text,sizeof(Text),"%s",*(char*)Data);
			break;
		case Track::FLOAT:
			sprintf_s(Text,sizeof(Text),"%f",*(float*)Data);
			break;
		case Track::INT:
			sprintf_s(Text,sizeof(Text),"%d",*(int*)Data);
			break;
		case Track::UINT:
			sprintf_s(Text,sizeof(Text),"%u",*(DWORD*)Data);
			break;
		default:
			sprintf_s(Text,sizeof(Text),"Unknown");
		}

	RECT Pos;
	Pos.left = X;
	Pos.top = Y;

	pFont->DrawText(NULL,Text,-1,&Pos,DT_LEFT|DT_NOCLIP,Color);
}
