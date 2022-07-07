#include "LaunchHightScore.h"
#include <SDL.h>
#include "Data.h"
#include <fstream>
#include <SDL_mixer.h>

using namespace data;
using namespace d34;

LaunchHightScore::LaunchHightScore(SDL_Renderer* _g_renderer,D34_SDL2& _g_D34_SDL2)
{
	g_renderer = _g_renderer;
	g_D34_SDL2 = _g_D34_SDL2;

	//gán NUM_HIGHT_SCORE người chơi vào mảng
	ifstream rf("hight_score.txt", ios::in);
	for (int i = 0; i < NUM_HIGHT_SCORE && !rf.eof(); i++) //mảng thông tin trong file luôn có NUM_HIGHT_SCORE phần tử
	{
		rf >> ary_player[i].name;
		rf >> ary_player[i].mark;
		rf >> ary_player[i].level;
		rf >> ary_player[i].num_block;
		rf >> ary_player[i].time_play;//đã xử lý nên phần thập phân chỉ có hàng đơn vị
	}
	rf.close();
	if (!rf.good()) cout << "\nError occurred at reading time!";

	// BUTTON EXIT
	btn_exit.Load_Context("Exit");
	btn_exit.Load_Context(d34_btn::FONT_STARCRAFT, 25);
	btn_exit.Load_Context(d34_btn::COLOR_WHITE);
	btn_exit.Set_Color_Button(d34_btn::COLOR_BLUE);
	btn_exit.Width(220);
	btn_exit.Height(50);
	btn_exit.X((SCREEN_WIDTH - btn_exit.Width()) / 2);
	btn_exit.Y(500);
}

LaunchHightScore::~LaunchHightScore() {}

void LaunchHightScore::Run()
{
	bool isRun = true;
	SDL_Event e;
	int font_size_board = 15;

	//Initialization Rect
	SDL_Rect rec_header{ 40,70,624,30 };//{x,y,w,h}
	SDL_Rect rec_stt = g_D34_SDL2.Load_Text(g_renderer, "STT", 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
	SDL_Rect rec_name = g_D34_SDL2.Load_Text(g_renderer, "Name", 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
	SDL_Rect rec_mark = g_D34_SDL2.Load_Text(g_renderer, "Mark", 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
	SDL_Rect rec_level = g_D34_SDL2.Load_Text(g_renderer, "Level", 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
	SDL_Rect rec_block = g_D34_SDL2.Load_Text(g_renderer, "Block", 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
	SDL_Rect rec_time = g_D34_SDL2.Load_Text(g_renderer, "Time", 0, -100, FONT_STARCRAFT, font_size_board, WHITE);

	//loop main
	while (isRun) {
		Sound_Hight_Score();
		#pragma region EVENT
		if (SDL_WaitEvent(&e)) {
			switch (e.type)
			{
			case SDL_QUIT:
				isRun = false;
				break;
			case SDL_MOUSEMOTION:
				// Animatio /////////////////////////////////////////////////////////////////////
				btn_exit.Animation(g_renderer, e.button.x, e.button.y, d34_btn::COLOR_WHITE, d34_btn::COLOR_RED);
				break;
			case SDL_MOUSEBUTTONDOWN:
				// Click ////////////////////////////////////////////////////////////////////
				if (btn_exit.IS_Mouse_In_Button(e.button.x, e.button.y)) 
				{
					btn_exit.Sound_Click();
					isRun = false;
				}
				break;
			}
		}
#pragma endregion

		#pragma region LOAD SCREEN
		SDL_RenderClear(g_renderer);
		g_D34_SDL2.Load_Image_BMP(g_renderer, "Background_hight_score.bmp", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		btn_exit.Load_Button(g_renderer);
#pragma region Load Board
		#pragma region load header
		g_D34_SDL2.D34_SetRenderDrawColor_RGB(g_renderer, CORN_FLOWER_BLUE);
		SDL_RenderFillRect(g_renderer, &rec_header);
		//STT
		rec_stt.x = 65 - rec_stt.w / 2;
		rec_stt.y = 85 - rec_stt.h / 2;
		rec_stt = g_D34_SDL2.Load_Text(g_renderer, "STT", rec_stt.x, rec_stt.y, FONT_STARCRAFT, font_size_board, WHITE);
		//Name
		rec_name.x = 190 - rec_name.w / 2;
		rec_name.y = 85 - rec_name.h / 2;
		rec_name = g_D34_SDL2.Load_Text(g_renderer, "Name", rec_name.x, rec_name.y, FONT_STARCRAFT, font_size_board, WHITE);
		//Mark
		rec_mark.x = 340 - rec_mark.w / 2;
		rec_mark.y = 85 - rec_mark.h / 2;
		rec_mark = g_D34_SDL2.Load_Text(g_renderer, "Mark", rec_mark.x, rec_mark.y, FONT_STARCRAFT, font_size_board, WHITE);
		//Level
		rec_level.x = 427 - rec_level.w / 2;
		rec_level.y = 85 - rec_level.h / 2;
		rec_level = g_D34_SDL2.Load_Text(g_renderer, "Level", rec_level.x, rec_level.y, FONT_STARCRAFT, font_size_board, WHITE);
		//Block
		rec_block.x = 514 - rec_block.w / 2;
		rec_block.y = 85 - rec_block.h / 2;
		rec_block = g_D34_SDL2.Load_Text(g_renderer, "Block", rec_block.x, rec_block.y, FONT_STARCRAFT, font_size_board, WHITE);
		//Time
		rec_time.x = 614 - rec_time.w / 2;
		rec_time.y = 85 - rec_time.h / 2;
		rec_time = g_D34_SDL2.Load_Text(g_renderer, "Time", rec_time.x, rec_time.y, FONT_STARCRAFT, font_size_board, WHITE);
#pragma endregion
#pragma region load content
		for (int i = 0; i < NUM_HIGHT_SCORE; i++)
		{
			if (ary_player[i].num_block > 0 && ary_player[i].mark>=0 && ary_player[i].level>0) {
				//xử lý lưu kiểu double 1 số sau dấu phẩy cho time_play
				string strtime = to_string(ary_player[i].time_play);
				strtime = strtime.substr(0, strtime.find('.', 0) + 2);
				SDL_Rect rec_content_stt = g_D34_SDL2.Load_Text(g_renderer, to_string(i+1), 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
				SDL_Rect rec_content_name = g_D34_SDL2.Load_Text(g_renderer, ary_player[i].name, 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
				SDL_Rect rec_content_mark = g_D34_SDL2.Load_Text(g_renderer, to_string(ary_player[i].mark), 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
				SDL_Rect rec_content_level = g_D34_SDL2.Load_Text(g_renderer, to_string(ary_player[i].level), 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
				SDL_Rect rec_content_block = g_D34_SDL2.Load_Text(g_renderer, to_string(ary_player[i].num_block),0, -100, FONT_STARCRAFT, font_size_board, WHITE);
				SDL_Rect rec_content_time = g_D34_SDL2.Load_Text(g_renderer, strtime, 0, -100, FONT_STARCRAFT, font_size_board, WHITE);
				//stt
			
				rec_content_stt.x = 65 - rec_content_stt.w / 2;
				rec_content_stt.y = 85 + (i+1) * 30 - rec_content_stt.h / 2;
				rec_content_stt = g_D34_SDL2.Load_Text(g_renderer, to_string(i+1), rec_content_stt.x, rec_content_stt.y, FONT_STARCRAFT, font_size_board, WHITE);
				//name
				
				rec_content_name.x = 190 - rec_content_name.w / 2;
				rec_content_name.y = 85 + (i + 1) * 30 - rec_content_name.h / 2;
				rec_content_name = g_D34_SDL2.Load_Text(g_renderer, ary_player[i].name, rec_content_name.x, rec_content_name.y, FONT_STARCRAFT, font_size_board, WHITE);
				//mark
				
				rec_content_mark.x = 340 - rec_content_mark.w / 2;
				rec_content_mark.y = 85 + (i + 1) * 30 - rec_content_mark.h / 2;
				rec_content_mark = g_D34_SDL2.Load_Text(g_renderer, to_string(ary_player[i].mark), rec_content_mark.x, rec_content_mark.y, FONT_STARCRAFT, font_size_board, WHITE);
				//level
				
				rec_content_level.x = 427 - rec_content_level.w / 2;
				rec_content_level.y = 85 + (i + 1) * 30 - rec_content_level.h / 2;
				rec_content_level = g_D34_SDL2.Load_Text(g_renderer, to_string(ary_player[i].level), rec_content_level.x, rec_content_level.y, FONT_STARCRAFT, font_size_board, WHITE);
				//block
				
				rec_content_block.x = 514 - rec_content_block.w / 2;
				rec_content_block.y = 85 + (i + 1) * 30 - rec_content_block.h / 2;
				rec_content_block = g_D34_SDL2.Load_Text(g_renderer, to_string(ary_player[i].num_block), rec_content_block.x, rec_content_block.y, FONT_STARCRAFT, font_size_board, WHITE);
				//time
				
				rec_content_time.x = 614 - rec_content_time.w / 2;
				rec_content_time.y = 85 + (i + 1) * 30 - rec_content_time.h / 2;
				rec_content_time = g_D34_SDL2.Load_Text(g_renderer, strtime, rec_content_time.x, rec_content_time.y, FONT_STARCRAFT, font_size_board, WHITE);
			}
		}
#pragma endregion

#pragma endregion
#pragma endregion


		//cout << "rec_stt(x,y)= (" << rec_stt.x << "," << rec_stt.y << ")" << endl;
		//cout << "rec_header(x,y)= (" << rec_header.x << "," << rec_header.y << ")" << endl;

		////Draw Line
		//g_D34_SDL2.D34_SetRenderDrawColor_RGB(g_renderer, WHITE);
		//SDL_RenderDrawLine(g_renderer, 90, 100, 90, 130);
		//SDL_RenderDrawLine(g_renderer, 290, 100, 290, 130);
		//SDL_RenderDrawLine(g_renderer, 390, 100, 390, 130);
		//SDL_RenderDrawLine(g_renderer, 464, 100, 464, 130);
		//SDL_RenderDrawLine(g_renderer, 564, 100, 564, 130);
		//DRAW
		SDL_RenderPresent(g_renderer);
	}

}

void LaunchHightScore::Sound_Hight_Score() {
	Mix_Music* music = Mix_LoadMUS("music_hight_score.mp3");
	if (music == NULL)
	{
		printf("%s", Mix_GetError());
	}
	if (!Mix_PlayingMusic()) Mix_PlayMusic(music, -1);
}