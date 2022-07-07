
#include <string>
#include "LaunchHome.h"
#include "D34_Button.h"
#include "LaunchPlay.h"
#include "LaunchHightScore.h"
#include "D34_SDL2.h"
#include <SDL_mixer.h>

using namespace d34;
using namespace d34_btn;

LaunchHome::LaunchHome(SDL_Renderer* _renderer, D34_SDL2& _D34_SDL2)
{
	g_renderer = _renderer;
	g_D34_SDL2 = _D34_SDL2;

	// BUTTON NEW GAME
	btn_newgame.Load_Context("New Game");
	btn_newgame.Load_Context(d34_btn::FONT_STARCRAFT, 25);
	btn_newgame.Load_Context(d34_btn::COLOR_WHITE);
	btn_newgame.Set_Color_Button(d34_btn::COLOR_BLUE);
	btn_newgame.Width(220);
	btn_newgame.Height(50);
	btn_newgame.X((SCREEN_WIDTH - btn_newgame.Width()) / 2);
	btn_newgame.Y(200);

	// BUTTON HIGHT SCORE
	btn_hightscore.Load_Context("Hight score");
	btn_hightscore.Load_Context(d34_btn::FONT_STARCRAFT, 25);
	btn_hightscore.Load_Context(d34_btn::COLOR_WHITE);
	btn_hightscore.Set_Color_Button(d34_btn::COLOR_BLUE);
	btn_hightscore.Width(220);
	btn_hightscore.Height(50);
	btn_hightscore.X((SCREEN_WIDTH - btn_hightscore.Width()) / 2);
	btn_hightscore.Y(270);

	// BUTTON EXIT
	btn_exit.Load_Context("Exit");
	btn_exit.Load_Context(d34_btn::FONT_STARCRAFT, 25);
	btn_exit.Load_Context(d34_btn::COLOR_WHITE);
	btn_exit.Set_Color_Button(d34_btn::COLOR_BLUE);
	btn_exit.Width(220);
	btn_exit.Height(50);
	btn_exit.X((SCREEN_WIDTH - btn_exit.Width()) / 2);
	btn_exit.Y(340);

	//Dừng LaunchHome 1s để chương trình load xong 
	SDL_Delay(1000);
}

LaunchHome::~LaunchHome() {
}

bool LaunchHome::Run() {
	bool isRun = true;
	SDL_Event e;

	//loop main
	while (isRun) {
		Sound_Background();
		//Event
		if (SDL_WaitEvent(&e)) {
			switch (e.type)
			{
			case SDL_QUIT:
				isRun=false;
				break;
			case SDL_MOUSEMOTION:
				// Animatio /////////////////////////////////////////////////////////////////////
				btn_newgame.Animation(g_renderer, e.button.x, e.button.y, d34_btn::COLOR_WHITE, d34_btn::COLOR_RED);
				btn_hightscore.Animation(g_renderer, e.button.x, e.button.y, d34_btn::COLOR_WHITE, d34_btn::COLOR_RED);
				btn_exit.Animation(g_renderer,e.button.x, e.button.y, d34_btn::COLOR_WHITE, d34_btn::COLOR_RED);
				break;
			case SDL_MOUSEBUTTONDOWN:
				// Click ////////////////////////////////////////////////////////////////////
				if (btn_newgame.IS_Mouse_In_Button(e.button.x, e.button.y))
				{
					btn_newgame.Sound_Click();
					LaunchPlay lan_play(g_renderer, g_D34_SDL2);
					lan_play.Run();
					btn_newgame.Load_Context(d34_btn::COLOR_WHITE);
				}	
				else if (btn_hightscore.IS_Mouse_In_Button(e.button.x, e.button.y)) {
					btn_hightscore.Sound_Click();
					LaunchHightScore lan_hight_score(g_renderer, g_D34_SDL2);
					lan_hight_score.Run();
					btn_hightscore.Load_Context(d34_btn::COLOR_WHITE);
				}
				else if (btn_exit.IS_Mouse_In_Button(e.button.x, e.button.y)) {
					btn_exit.Sound_Click();
					isRun = false;
				}
				break;
			}
		}

		//LOAD SCREEN ///////////////////////////////////////////////////
		SDL_RenderClear(g_renderer);
		g_D34_SDL2.Load_Image_BMP(g_renderer, "Tetris_background.bmp", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		btn_newgame.Load_Button(g_renderer);
		btn_hightscore.Load_Button(g_renderer);
		btn_exit.Load_Button(g_renderer);

		//DRAW
		SDL_RenderPresent(g_renderer);
	}

	return false;
}

void LaunchHome::Sound_Background() {
	Mix_Music* music = Mix_LoadMUS("music_menu.mp3");
	if (music == NULL)
	{
		printf("%s", Mix_GetError());
	}
    if(!Mix_PlayingMusic()) Mix_PlayMusic(music, -1);
}