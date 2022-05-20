

#include <iostream>
#include "tetris.h"

/* 0  1  2  3
   4  5  6  7 */

const int Tetris::figures[7][4] =
{
	0,1,2,3,	// I
	0,4,5,6,	// J
	2,6,5,4,	// L
	1,2,5,6,	// O
	2,1,5,4,	// S
	1,4,5,6,	// T
	0,1,5,6,	// Z
};


void Tetris::holds(int& countHold)
{
    if(countHold == 0)
    {
        if (hold[0].figures == -1)
        {
            for (int i = 0; i < 4; i++)
            {
                hold[i].x = items[i].x;
                hold[i].y = items[i].y;
                hold[i].figures = items[i].figures;
                hold[i].color = items[i].color;
            }

            nextTetrimino();
        }
        else
        {
            Point tmp[4];

            for (int i = 0; i < 4; i++)
            {
                tmp[i].x = hold[i].x;
                hold[i].x = items[i].x;
                items[i].x = tmp[i].x;

                tmp[i].y = hold[i].y;
                hold[i].y = items[i].y;
                items[i].y = tmp[i].y;

                tmp[i].figures = hold[i].figures;
                hold[i].figures = items[i].figures;
                items[i].figures = tmp[i].figures;

                tmp[i].color = hold[i].color;
                hold[i].color = items[i].color;
                items[i].color = tmp[i].color;
            }
            color = items[0].color;

        }
        resetTetrimino();
        countHold++;
    }
}

void Tetris::resetTetrimino()
{
    for (int i = 0; i < 4; i++)
    {
        hold[i].x = figures[hold[i].figures][i] % 4 ;
		hold[i].y = int(figures[hold[i].figures][i] / 4);
    }
}

void Tetris::nextTetrimino()
{

    checkLines();
    write = false;
    if (items[0].figures == -1 ) next();
	for (int i = 0; i < 4; i++)
	{
		items[i].x = nextItem[i].x;
        items[i].y = nextItem[i].y;
        items[i].figures = nextItem[i].figures;
        items[i].color = nextItem[i].color;
	}
    next();
}

void Tetris::next()
{
    SDL_Delay(200);
    int n = rand() % 7;
	color = n + 1;
    for (int i = 0; i < 4; i++)
	{
		nextItem[i].x = figures[n][i] % 4 + 3;
		nextItem[i].y = int(figures[n][i] / 4) ;
		nextItem[i].figures = n;
		nextItem[i].color = n+1;
	}
}

void Tetris::pause()
{
    if (doMove == true)
    {
        for(int i = 0; i < 4; i++) backup[i] = items[i];
        move();
        tick();
    }
}

void Tetris::handleEvents()
{
	SDL_Event e;
	countHold = 0;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = false;
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				gRotate();
				break;
			case SDLK_LEFT:
				dx = -1;
				break;
			case SDLK_RIGHT:
				dx = 1;
				break;
            case SDLK_c:
                holds(countHold);
                break;
            case SDLK_v:
                pause();
                doMove = (doMove + 1) % 2;
                break;
			default:
				break;
			}
		default:
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN])
		delay = 40;
    else if (state[SDL_SCANCODE_SPACE])
        delay = 3.5;
    else delay = 500 - lev * 20;
}

bool Tetris::isvalid()
{
	for (int i = 0; i < 4; i++)
		if (items[i].x < 0 || items[i].x >= Cols || items[i].y >= Lines)
			return false;
		else if (field[items[i].y][items[i].x])
			return false;
	return true;
}

bool Tetris::gameover()
{
    bool returnning = false;
    for (int i = 3; i <= 6; i++)
    {
        if (field[0][i])
        {
            SDL_Delay(10);
            break;
        }
    }
    for (int i = 3; i <= 6; i++)
    {
        if (field[0][i])
        {
            returnning = true;
            running = false;
        }
    }
    return returnning;
}

void Tetris::move()
{
    if (dx)
    {
        for (int i = 0; i < 4; i++)
        {
            items[i].x += dx;
        }
        if (!isvalid())
            for (int i = 0; i < 4; i++)
                items[i] = backup[i];
    }
    dx = 0;
}

void Tetris::tick()
{
    if (currentTime - startTime > delay)
	{
		for (int i = 0; i < 4; i++)
			backup[i] = items[i];
		for (int i = 0; i < 4; i++)
			items[i].y++;
		if (!isvalid())
		{
			for (int i = 0; i < 4; i++)
				field[backup[i].y][backup[i].x] = backup[i].color;
			nextTetrimino();
		}

		startTime = currentTime;
	}
}

void Tetris::level()
{
    lev = score / 100;
}

void Tetris::checkLines()
{
    int numLines = 0;
    int k = Lines - 1;
        for (int i = k; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < Cols; j++)
            {
                if (field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            if (count == Cols) numLines++;
            if (count < Cols)
            {
                k--;
            }
        }
        switch(numLines)
        {
            case 1: score+=10; break;
            case 2: score+=20; break;
            case 3: score+=40; break;
            case 4: score+=80; break;
            default: break;
        }
        level();
}

void Tetris::gRotate()
{
            Point p = items[2];	// center of rotation
            for (int i = 0; i < 4; i++)
            {
                int x = items[i].y - p.y;
                int y = items[i].x - p.x;
                items[i].x = p.x - x;
                items[i].y = p.y + y;
            }
            if (!isvalid())
                for (int i = 0; i < 4; i++)
                    items[i] = backup[i];
}

void Tetris::gameplay()
{
    if(!gameover() && doMove)
    {
        ////////// backup
        for (int i = 0; i < 4; i++)
            backup[i] = items[i];
        ////////// move
        move();
        ///////// tick
        tick();
    }
}

