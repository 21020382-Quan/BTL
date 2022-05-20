#include "replay.h"

bool Replay::checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

bool Replay::initReplay(const char* title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 640, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return -1;
	}


    font = TTF_OpenFont("VeraMoBd.ttf", 60);
	ft = TTF_OpenFont("VeraMoBd.ttf", 30);

}

void Replay::setUp()
{
    textReplay();
    handle();
}

void Replay::textReplay()
{
    // FONT
	std::string text = "TETRIS";
	surface = TTF_RenderText_Solid(font, text.c_str(), fgTetris);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

	srcRest.x = 0;
	srcRest.y = 0;

	desRect.x = 100;
	desRect.y = 100;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;

    //PLAY
	std::string mainmenu = "MAIN MENU";
	sMainmenu = TTF_RenderText_Solid(ft, mainmenu.c_str(), fgMainmenu);
	tMainmenu = SDL_CreateTextureFromSurface(renderer, sMainmenu);
	SDL_FreeSurface(sMainmenu);

	TTF_SizeText(ft, mainmenu.c_str(), &srcMainmenuR.w, &srcMainmenuR.h);

	srcMainmenuR.x = 0;
	srcMainmenuR.y = 0;

	desMainmenuR.x = 120;
	desMainmenuR.y = 300;

	desMainmenuR.w = srcMainmenuR.w;
	desMainmenuR.h = srcMainmenuR.h;

	//EXIT
	std::string exit = "EXIT";
	sExit = TTF_RenderText_Solid(ft, exit.c_str(), fgExit);
	tExit = SDL_CreateTextureFromSurface(renderer, sExit);
	SDL_FreeSurface(sExit);

	TTF_SizeText(ft, exit.c_str(), &srcExitR.w, &srcExitR.h);

	srcExitR.x = 0;
	srcExitR.y = 0;

	desExitR.x = 120;
	desExitR.y = 400;

	desExitR.w = srcExitR.w;
	desExitR.h = srcExitR.h;
}

void Replay::handle()
{
    while (isRunning)
	{
		while (SDL_PollEvent(&mainEvent))
		{
            switch (mainEvent.type)
            {
                case SDL_QUIT:
                {
                    isRunning = false;
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    x = mainEvent.motion.x;
                    y = mainEvent.motion.y;

                    if (checkFocusWithRect(x, y, desMainmenuR))
                    {
                        fgMainmenu = {243, 156, 18};
                    }
                    else if (checkFocusWithRect(x, y, desExitR))
                    {
                        fgExit = {243, 156, 18};
                    }
                    else
                    {
                        fgMainmenu = {255, 255, 255};
                        fgExit = {255, 255, 255};
                    }
                    textReplay();
                    handle();
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    x = mainEvent.button.x;
                    y = mainEvent.button.y;

                    if (checkFocusWithRect(x, y, desMainmenuR))
                    {
                        again = true;
                    }
                    else if (checkFocusWithRect(x, y, desExitR))
                    {
                        quit = true;
                    }
                    isRunning = false;
                    break;
                }
                default:
                    break;
            }
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
		SDL_RenderCopy(renderer, tMainmenu, &srcMainmenuR, &desMainmenuR);
		SDL_RenderCopy(renderer, tExit, &srcExitR, &desExitR);
		SDL_RenderPresent(renderer);
	}
}

void Replay::clean()
{
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}
