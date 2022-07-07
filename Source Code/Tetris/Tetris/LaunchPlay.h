#ifndef _LAUNCH_PLAY_H_
#define _LAUNCH_PLAY_H_

#include <SDL.h>
#include "ManageTetromino.h"
#include "Tetromino.h"
#include "Data.h"
#include "D34_SDL2.h"
#include "D34_Button.h"
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>

using namespace d34;
using namespace data;

class LaunchPlay
{
public:
	LaunchPlay(SDL_Renderer* _g_renderer, D34_SDL2& _D34_SDL2);
	~LaunchPlay();

	bool Enter_Name();
	bool Run();
	void Save_Info_Player();
	void Lost();
	void Sound_Play();
	void Sound_KeyBoard();
	void Sound_Lost();
private:
	SDL_Renderer* g_renderer;
	D34_SDL2 g_D34_SDL2;
	ManageTetromino manage_;
	Tetromino tetromino_;
	clock_t time_start;
	int hight_mark;
	double speed;
	Info_Player player;

	//Button
	d34_btn::D34_Button btn_exit;

};

#endif // !_LAUNCH_PLAY_H_