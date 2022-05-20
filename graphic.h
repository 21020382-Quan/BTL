#pragma once
#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "tetris.h"

class Graphic
{

private:
    enum { ScreenW = 400, ScreenH = 640 };
	enum { BlockW = 24, BlockH = 24 };
	enum { Lines = 20, Cols = 10 };
    SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	SDL_Texture* background = NULL, * blocks = NULL, * tScore = NULL, * tLevel = NULL, * tHigh = NULL;
	SDL_Surface* surface = NULL;
	SDL_Rect srcR = { 0, 0, BlockW, BlockH }, destR = { 0, 0, BlockW, BlockH }, srcNextR= { 0, 0, BlockW, BlockH }, desNextR= { 0, 0, BlockW, BlockH },
             srcScoreR = {0, 0, 0, 0}, desScoreR = {0, 0, 0, 0}, srcLevelR = {0, 0, 0, 0}, desLevelR = {0, 0, 0, 0};
    TTF_Font *font = NULL;
    SDL_Color fg = {255, 255, 255};

    Tetris tetris_;
    bool write = true;
    bool running = false;

public:
    Graphic()
    {
    }
    ~Graphic()
    {
    }
    bool cfquit()
    {
        return tetris_.quit;
    }
    bool init(const char* title);
    void updateRender();
    void textScore();
    void setRectPos(SDL_Rect& rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
	void moveRectPos(SDL_Rect& rect, int x, int y);
	void clean();
	void play();
	void textLevel();

	bool isrunning()
	{
	    return tetris_.running;
	}
};

#endif // GRAPHIC_H_
