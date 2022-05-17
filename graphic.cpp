#include "graphic.h"
#include <iostream>
using namespace std;

bool Graphic::init(const char* title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
		if (window != NULL)
		{
			render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (render != NULL)
			{
			    int imgFlags = IMG_INIT_PNG;
				int initted = IMG_Init(imgFlags);
				if ((initted & imgFlags) != imgFlags)
					std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
				SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
				SDL_Surface* loadSurf = IMG_Load("bkgn.png");
				background = SDL_CreateTextureFromSurface(render, loadSurf);
				SDL_FreeSurface(loadSurf);
				loadSurf = IMG_Load("blocks.png");
				blocks = SDL_CreateTextureFromSurface(render, loadSurf);
				SDL_FreeSurface(loadSurf);
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
    if (TTF_Init() < 0) return false;
    font = TTF_OpenFont("VeraMoBd.ttf", 18);
    lv = TTF_OpenFont("VeraMoBd.ttf", 18);
	running = true;
	tetris_.running = true;
	return true;
}

void Graphic::play()
{
    tetris_.setCurrentTime(SDL_GetTicks());
    tetris_.handleEvents();
    tetris_.gameplay();
    if(tetris_.write == false) textScore();
    updateRender();
}

void Graphic::textScore()
{
    string text = to_string(tetris_.score);
    tScore = SDL_CreateTextureFromSurface(render, TTF_RenderText_Solid(font, text.c_str(), fg));
    TTF_SizeText(font, text.c_str(), &srcScoreR.w, &srcScoreR.h);
    srcScoreR.x = 0;
    srcScoreR.y = 0;

    desScoreR.x = 350;
    desScoreR.y = 402;

    desScoreR.w = srcScoreR.w;
    desScoreR.h = srcScoreR.h;
    tetris_.write = true;
}

void Graphic::setRectPos(SDL_Rect& rect, int x, int y, int w, int h)
{
	rect = { x, y, w, h };
}

void Graphic::moveRectPos(SDL_Rect& rect, int x, int y)
{
	rect.x += x;
	rect.y += y;
}

void Graphic::updateRender()
{

	SDL_RenderCopy(render, background, NULL, NULL);
	for (int i = 0; i < Lines; i++)
		for (int j = 0; j < Cols; j++)
			if (tetris_.field[i][j])
			{
				setRectPos(srcR, tetris_.field[i][j] * BlockW);
				setRectPos(destR, j * BlockW, i * BlockH);
				moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
				SDL_RenderCopy(render, blocks, &srcR, &destR);
			}
	for (int i = 0; i < 4; i++)
	{
		setRectPos(srcR, tetris_.items[i].color * BlockW);
		setRectPos(destR, tetris_.items[i].x * BlockW, tetris_.items[i].y * BlockH);
        moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
		SDL_RenderCopy(render, blocks, &srcR, &destR);
	}

	for (int i = 0; i < 4; i++)
	{
		setRectPos(srcR, tetris_.hold[i].color * BlockW);
		setRectPos(destR, (tetris_.hold[i].x + 11)* BlockW , (tetris_.hold[i].y + 7) * BlockH);
        moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
		SDL_RenderCopy(render, blocks, &srcR, &destR);
	}

	for (int i = 0; i < 4; i++)
	{
		setRectPos(srcNextR, tetris_.nextItem[i]. color * BlockW);
		setRectPos(desNextR, (tetris_.nextItem[i].x + 8)* BlockW , (tetris_.nextItem[i].y + 1.5) * BlockH);
        moveRectPos(desNextR, BlockW, ScreenH - (Lines + 1) * BlockH);
		SDL_RenderCopy(render, blocks, &srcNextR, &desNextR);
	}
    SDL_RenderCopy(render, tScore, &srcScoreR, &desScoreR);
    SDL_RenderCopy(render, tLevel, &srcLevelR, &desLevelR);
    SDL_RenderPresent(render);

}

void Graphic::textLevel()
{
    string text = to_string(tetris_.lev);
    tLevel = SDL_CreateTextureFromSurface(render, TTF_RenderText_Solid(lv, text.c_str(), fg));
    TTF_SizeText(lv, text.c_str(), &srcLevelR.w, &srcLevelR.h);
    srcLevelR.x = 0;
    srcLevelR.y = 0;

    desLevelR.x = 350;
    desLevelR.y = 437;

    desLevelR.w = srcLevelR.w;
    desLevelR.h = srcLevelR.h;
}

void Graphic::clean()
{
	SDL_DestroyTexture(blocks);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(tScore);
	SDL_DestroyTexture(tLevel);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
