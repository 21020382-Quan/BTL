
#include "tetris.h"
#include <iostream>
#include <ctime>
#include "graphic.h"


int main(int argc, char* argv[])
{
	using namespace std;
	srand(time(0));
	Graphic* graphic = new Graphic();
	const char* title = "Tetris";
	if (graphic->init(title))
	{
		while (graphic->isrunning())
		{
			graphic->play();
		}
	}
	else
	{
		cout << "Failed to initialize";
	}

	graphic->clean();

	return 0;
}

