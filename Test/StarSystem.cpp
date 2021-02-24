#include <cstdint>
class StarSystem
{
public:
	StarSystem(uint32_t x, uint32_t y)
	{
		nLehmer = (x & 0xFFFF) << 16 | (y & 0xFFFF);
	}

private:
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

};