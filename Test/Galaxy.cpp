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

	uint32_t nLehmer = 0;
	uint32_t Lehmer32()
	{
		nLehmer += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)nLehmer * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}


	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::SPACE).bReleased) {
			Clear(olc::BLACK);

			//----------std::random----------
			//std::random_device rd;
			//std::mt19937 mt(rd());
			//std::uniform_int_distribution<int> dist(0, 256);
			//-------------------------------

			auto genStartTime = std::chrono::system_clock::now();

			for (int x = 0; x < ScreenWidth(); x++) {
				for (int y = 0; y < ScreenHeight(); y++)
				{
					bool bIsStar = false;
					int nSeed = y << 16 | x;

					//----------Standard C++ rand()----------
					//srand(nSeed);
					//biIsStar=rand()%256<128;
					//---------------------------------------

					//----------std::random----------
					//mt.seed(nSeed);
					//bIsStar = dist(mt) < 32;
					//-------------------------------

					//----------Lehmer32----------
					nLehmer = nSeed;
					bIsStar = Lehmer32() % 256 < 32;
					//----------------------------
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

