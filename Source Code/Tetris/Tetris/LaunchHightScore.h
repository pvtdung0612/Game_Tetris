#ifndef _LAUNCH_HIGHT_SCORE_H_
#define _LAUNCH_HIGHT_SCORE_H_

#include <SDL.h>
#include "D34_SDL2.h"
#include "D34_Button.h"
#include "Data.h"
#include <vector>

using namespace d34;
using namespace data;

class LaunchHightScore
{
public:
	LaunchHightScore(SDL_Renderer* _g_renderer, D34_SDL2& _g_D34_SDL2);
	~LaunchHightScore();

	void Run();
	void Sound_Hight_Score();
private:
	SDL_Renderer* g_renderer;
	D34_SDL2 g_D34_SDL2;

	Info_Player ary_player[NUM_HIGHT_SCORE];

	d34_btn::D34_Button btn_exit;
};
#endif // !_LAUNCH_HIGHT_SCORE_H_

/*
rec_header
rec_rank 
rec_name 
rec_mark 
rec_level 
rec_block 
rec_time 
*/
