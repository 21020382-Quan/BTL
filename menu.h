#pragma once
#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Menu
{
public:
    Menu()
    {
    }
    ~Menu()
    {
    }
    bool initMenu(const char* title);
    void handle();
    void textMenu();
    void clean();
    void setUp();
    bool start = false, quit = false;
    string play;
    bool checkFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
private:
    const char* title;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool isRunning = true;
	SDL_Event mainEvent;
	TTF_Font* font = NULL, * ft = NULL;
	SDL_Surface* surface = NULL, * sPlay = NULL, * sExit = NULL;
	SDL_Texture* texture = NULL, * tPlay = NULL, * tExit = NULL;
	SDL_Rect srcRest = {0, 0, 0, 0}, desRect = {0, 0, 0, 0}, srcPlayR = {0, 0, 0, 0}, desPlayR = {0, 0, 0, 0}, srcExitR = {0, 0, 0, 0}, desExitR = {0, 0, 0, 0};
	SDL_Color fgTetris = {255, 255, 255}, fgPlay = {255, 255, 255}, fgExit = {255, 255, 255};
	int x = 0, y = 0;
};

#endif // MENU_H_

