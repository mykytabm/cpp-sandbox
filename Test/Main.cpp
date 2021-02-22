#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "Game";
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
		sprIsom = new olc::Sprite("land.png");
		world = new int[worldSize.x * worldSize.y]{ 0 };
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::WHITE);

		olc::vi2d vMouse = { GetMouseX(),GetMouseY() };
		olc::vi2d vCell = { vMouse.x / vTileSize.x,vMouse.y / vTileSize.y };
		olc::vi2d vOffset = { vMouse.x % vTileSize.x,vMouse.y % vTileSize.y };
		olc::Pixel col = sprIsom->GetPixel(3 * vTileSize.x + vOffset.x, vOffset.y);

		olc::vi2d vSelected =
		{
			(vCell.y - vOrigin.y) + (vCell.x - vOrigin.x),
			(vCell.y - vOrigin.y) - (vCell.x - vOrigin.x)
		};


		auto ToScreen = [&](int x, int y)
		{
			return olc::vi2d
			{
				(vOrigin.x * (vTileSize.x)) + (x - y) * (vTileSize.x / 2),
				(vOrigin.y * (vTileSize.y)) + (x + y) * (vTileSize.y / 2)
			};
		};

		SetPixelMode(olc::Pixel::MASK);

		for (int y = 0; y < worldSize.y; y++)
		{
			for (int x = 0; x < worldSize.x; x++)
			{
				olc::vi2d  vWorld = ToScreen(x, y);
				switch (world[y * worldSize.x + x])
				{
				case 0:
					DrawSprite(vWorld, sprIsom);
					break;
				}
			}
		}

		SetPixelMode(olc::Pixel::ALPHA);
		olc::vi2d vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
		DrawSprite(vSelectedWorld.x, vSelectedWorld.y, sprIsom);

		SetPixelMode(olc::Pixel::NORMAL);

		DrawString(4, 4, "Mouse   : " + std::to_string(vMouse.x) + ", " + std::to_string(vMouse.y), olc::BLACK);
		DrawString(4, 14, "Cell   : " + std::to_string(vCell.x) + ", " + std::to_string(vCell.y), olc::BLACK);
		DrawString(4, 24, "Cell   : " + std::to_string(vSelected.x) + ", " + std::to_string(vSelected.y), olc::BLACK);
		DrawRect(vCell.x * vTileSize.x, vCell.y * vTileSize.y, vTileSize.x, vTileSize.y, olc::RED);
		return true;
	}
};

int main()
{
	Game game;
	if (game.Construct(500, 300, 2, 2))
		game.Start();

	return 0;
}