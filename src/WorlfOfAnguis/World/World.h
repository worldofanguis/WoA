

#include "Common.h"
#include "Graphics/World/DXWorldView.h"

class World : DXWorldView
{
public:
	World();
	~World();
	
	static void SetSize(int Width,int Height) {World::Width = Width; World::Height = Height;}
	static int GetWidth() {return Width;}
	static int GetHeight() {return Height;}
	
	void Draw(int Left,int Top,int Width,int Height) {DXWorldView::Draw(Left,Top,Width,Height);}
private:
	char *Map;
	
	static int Width;
	static int Height;
};