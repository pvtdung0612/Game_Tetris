#ifndef _LAUNCH_HOME_H_
#define _LAUNCH_HOME_H_

#include <SDL.h>
#include "D34_Button.h"
#include "D34_SDL2.h"

using namespace d34;

class LaunchHome
{
public:
	LaunchHome(SDL_Renderer*, D34_SDL2&);
	~LaunchHome();

	bool Run();
	void Sound_Background();
private:
	const int SCREEN_WIDTH = 705;
	const int SCREEN_HEIGHT = 610;
	SDL_Renderer* g_renderer;
	D34_SDL2 g_D34_SDL2;
	d34_btn::D34_Button btn_newgame;
	d34_btn::D34_Button btn_hightscore;
	d34_btn::D34_Button btn_exit;
};
#endif // !_LAUNCH_HOME_H_
