#pragma once
#ifndef REPLAY_H_
#define REPLAY_H_

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "tetris.h"

using namespace std;

class Replay
{
public:
    Replay()
    {
    }
    ~Replay()
    {
    }
    bool initReplay(const char* title);
    void handle();
    void textReplay();
    void clean();
    void setUp();
    bool checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
    bool quit = false, again = false;
private:
    const char* title;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool isRunning = true;
	SDL_Event mainEvent;
	TTF_Font* font = NULL, * ft = NULL;
	SDL_Surface* surface = NULL, * sMainmenu = NULL, * sExit = NULL;
	SDL_Texture* texture = NULL, * tMainmenu = NULL, * tExit = NULL;
	SDL_Rect srcRest = {0, 0, 0, 0}, desRect = {0, 0, 0, 0}, srcMainmenuR = {0, 0, 0, 0}, desMainmenuR = {0, 0, 0, 0}, srcExitR = {0, 0, 0, 0}, desExitR = {0, 0, 0, 0};
	SDL_Color fgTetris = {255, 255, 255}, fgMainmenu = {255, 255, 255}, fgExit = {255, 255, 255};
	int x = 0, y = 0;

};

#endif // MENU_H_
