
#include "tetris.h"
#include <iostream>
#include <ctime>
#include "graphic.h"
#include "menu.h"
#include "replay.h"


int main(int argc, char* argv[])
{
	using namespace std;
	srand(time(0));
	Graphic* graphic = new Graphic();
	Menu* menu = new Menu();
	Replay* replay = new Replay();
	const char* title = "Tetris";
	while(true)
    {
        menu = new Menu();
        if (menu->initMenu(title))
        {
            menu->setUp();
            if (menu->start)
            {
                graphic = new Graphic();
                if (graphic->init(title))
                {
                    while (graphic->isrunning())
                    {
                        graphic->play();
                    }
                    if(!graphic->cfquit())
                    {
                        replay = new Replay();
                        if (replay->initReplay(title)) replay->setUp();
                        if (replay->quit)
                        {
                            replay->clean();
                            break;
                        }
                        if (replay->again)
                        {
                            graphic->clean();
                        }
                    }
                    else break;

                }
                else break;
            }
        else if (menu->quit)
        {
            menu->clean();
            break;
        }
        }
    }

	return 0;
}

