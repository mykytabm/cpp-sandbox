#include "Galaxy.cpp"
int main()
{
	Galaxy galaxy;
	if (galaxy.Construct(640, 480, 1, 1))
		galaxy.Start();

	return 0;
}