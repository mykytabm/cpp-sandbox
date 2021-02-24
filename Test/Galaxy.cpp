#include "olcPixelGameEngine.h"
#include <random>

// procedurally generated Galaxy

class Galaxy : public olc::PixelGameEngine
{
public:
	Galaxy()
	{
		sAppName = "Galaxy";
	}
private:

public:

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::SPACE).bReleased) {

			Clear(olc::BLACK);
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(0, 256);

			auto genStartTime = std::chrono::system_clock::now();

			for (int x = 0; x < ScreenWidth(); x++) {
				for (int y = 0; y < ScreenHeight(); y++)
				{
					bool bIsStar = false;
					int nSeed = y << 16 | x;

					bIsStar = dist(mt) < 32;
					Draw(x, y, bIsStar ? olc::WHITE : olc::BLACK);
				}
			}
			auto genEndTime = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = genEndTime - genStartTime;
			DrawString(3, 3, "Time: " + std::to_string(elapsedTime.count()), olc::RED, 2);
		}


		return true;
	}
};

