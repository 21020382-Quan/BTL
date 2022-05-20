
#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <typeinfo>
#include <iostream>

using namespace std;

class Tetris
{
public:
	Tetris()
	{
	}
	~Tetris()
	{
	}

	void setCurrentTime(Uint32 t)
	{
		currentTime = t;
	}

	bool isrunning()
	{
		return running;
	}
	bool quit = false;

	bool isvalid();

	void holds(int& countHold);
	void resetTetrimino();
	void reset();
	void pause();
	void nextTetrimino();
	void next();
	bool gameover();
	void handleEvents();
	void gameplay();
	void gRotate();
	void move();
	void tick();
	void checkLines();
	void level();

	enum { ScreenW = 400, ScreenH = 640 };
	enum { BlockW = 24, BlockH = 24 };
	enum { Lines = 20, Cols = 10 };
	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	SDL_Texture* background = NULL, * blocks = NULL, * texture = NULL;
	SDL_Surface* surface = NULL;

	SDL_Rect srcR = { 0, 0, BlockW, BlockH }, destR = { 0, 0, BlockW, BlockH }, srcNextR= { 0, 0, BlockW, BlockH }, desNextR= { 0, 0, BlockW, BlockH },
             srcScoreR = {0, 0, 0, 0}, desScoreR = {0, 0, 0, 0}, srcLevelR = {0, 0, 0, 0}, desLevelR = {0, 0, 0, 0};
    TTF_Font *font = NULL;
    SDL_Color fg = {255, 255, 255};

	bool running = false;
	int field[Lines][Cols] = { 0 };
	static const int figures[7][4];
	struct Point
	{
		int x, y, figures, color;
		Point()
		{
		    x = -1;
		    y = -1;
		    figures = -1;
		    color = -1;
		}
		Point(int _figures)
		{
		    figures = _figures;
		}
		Point(int _x, int _y)
		{
		    x = _x;
		    y = _y;
		}
	} items[4], backup[4], hold[4], nextItem[4];

	int countHold = 0;
	int color = 1;
	int dx = 0;
    int doMove = 1;
    int lev = 0, score = 0;
	bool rotate = false;
	unsigned int delay = 300;
	Uint32 startTime = 0, currentTime = 0;
	bool write = true;

};


#endif // !TETRIS_H_
