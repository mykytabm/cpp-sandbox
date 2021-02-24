#include "olcPixelGameEngine.h"

// not finished
class Galaxy : public olc::PixelGameEngine
{
public:
	Galaxy()
	{
		sAppName = "Galaxy";
	}
private:
	olc::vi2d worldSize = { 5,6 };
	olc::vi2d vTileSize = { 128,64 };
	olc::vi2d vOrigin = { 2,0 };
	olc::Sprite* sprIsom = nullptr;
	int* world = nullptr;
public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::WHITE);

		return true;
	}
};

