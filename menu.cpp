#include "menu.h"

bool Menu::checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

bool Menu::initMenu(const char* title)
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

void Menu::setUp()
{
    textMenu();
    handle();
}

void Menu::textMenu()
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
    play = "PLAY";
	sPlay = TTF_RenderText_Solid(ft, play.c_str(), fgPlay);
	tPlay = SDL_CreateTextureFromSurface(renderer, sPlay);
	SDL_FreeSurface(sPlay);

	TTF_SizeText(ft, play.c_str(), &srcPlayR.w, &srcPlayR.h);

	srcPlayR.x = 0;
	srcPlayR.y = 0;

	desPlayR.x = 120;
	desPlayR.y = 300;

	desPlayR.w = srcPlayR.w;
	desPlayR.h = srcPlayR.h;

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

void Menu::handle()
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
                    quit = true;
                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    x = mainEvent.motion.x;
                    y = mainEvent.motion.y;

                    if (checkFocusWithRect(x, y, desPlayR))
                    {
                        fgPlay = {243, 156, 18};
                    }
                    else if (checkFocusWithRect(x, y, desExitR))
                    {
                        fgExit = {243, 156, 18};
                    }
                    else
                    {
                        fgExit = {255, 255, 255};
                        fgPlay = {255, 255, 255};
                    }
                    textMenu();
                    handle();
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    x = mainEvent.button.x;
                    y = mainEvent.button.y;

                    if (checkFocusWithRect(x, y, desPlayR))
                    {
                        clean();
                        start = true;
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
		SDL_RenderCopy(renderer, tPlay, &srcPlayR, &desPlayR);
		SDL_RenderCopy(renderer, tExit, &srcExitR, &desExitR);
		SDL_RenderPresent(renderer);
	}
}

void Menu::clean()
{
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(tPlay);
	SDL_DestroyTexture(tExit);
	TTF_Quit();
	SDL_Quit();
}
