#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SDL_mixer.h"
#include "D34_Button.h"
#include "LaunchHome.h"
#include "Data.h"
#include "D34_SDL2.h"
#include <windows.h>

#undef main

using namespace d34;
using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_renderer;
D34_SDL2 g_D34_SDL2;

bool Init();
void Quit();

int main() {
	HWND window;
	AllocConsole();
	window = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(window, 0);

	if (Init()) {
		LaunchHome lau_home(g_renderer, g_D34_SDL2);
		lau_home.Run();

		Quit();
	}
	return 0;
}

bool Init() {
	g_window = NULL;
	g_renderer = NULL;

	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return false;
	}

	//Initialize the truetype font API.
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return false;
	}

	//Initialize the SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
	}

	//Create window
	g_window = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, data::SCREEN_WIDTH, data::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return false;
	}
	SDL_Surface* icon = IMG_Load("tetris_icon.bmp");
	SDL_SetWindowIcon(g_window, icon);

	//create a renderer
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return false;
	}

	//Init SDL_Image
	int imgFlags;
	imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}	imgFlags = IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}	imgFlags = IMG_INIT_TIF;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
}

void Quit() {
    SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	Mix_CloseAudio();
	TTF_Quit();
    IMG_Quit();
	SDL_Quit();
}