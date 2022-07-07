#include "ManageTetromino.h"
#include "Tetromino.h"
#include "D34_SDL2.h"
#include <SDL_mixer.h>

using namespace d34;

ManageTetromino::ManageTetromino()
{
	for (int x = 0; x < data::NUM_WIDTH; x++)
	{
		for (int y = 0; y < data::NUM_HEIGHT; y++)
		{
			data[x][y] = '0';
		}
	}
}
ManageTetromino::~ManageTetromino() {}

void ManageTetromino::Draw(SDL_Renderer* g_renderer, D34_SDL2& g_D34_SDL2) {
	//draw bacground board
	g_D34_SDL2.Load_Image_BMP(g_renderer, "Background_board_brick.bmp", board_x, board_y, board_w, board_h);


	//draw block
	for (int x = 0; x < data::NUM_WIDTH; x++)
	{
		for (int y = 0; y < data::NUM_HEIGHT; y++)
		{
			if (data[x][y] != '0') {
				switch (data[x][y]) {
				case 'I':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_light_blue.bmp", data::BORDER + x * data::CELL_SIZE,data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case 'J':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_orange.bmp", data::BORDER + x * data::CELL_SIZE, data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case 'L':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_blue.bmp", data::BORDER + x * data::CELL_SIZE, data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case 'O':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_yellow.bmp", data::BORDER + x * data::CELL_SIZE, data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case 'S':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_green.bmp", data::BORDER + x * data::CELL_SIZE, data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case 'T':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_purple.bmp", data::BORDER + x * data::CELL_SIZE, data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case 'Z':
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_red.bmp", data::BORDER + x * data::CELL_SIZE, data::BORDER + y * data::CELL_SIZE, data::CELL_SIZE, data::CELL_SIZE);
					break;
				}
				//draw block
				//SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, 255);
				//SDL_Rect rec_outsize{
				//	x * data::CELL_SIZE + data::BORDER,
				//	y * data::CELL_SIZE + data::BORDER,
				//	data::CELL_SIZE,
				//	data::CELL_SIZE };
				//SDL_RenderFillRect(g_renderer, &rec_outsize);

				//SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
				//SDL_Rect rec_insize{
				//	x * data::CELL_SIZE + data::BORDER + data::BORDER_CELL,
				//	y * data::CELL_SIZE + data::BORDER + data::BORDER_CELL,
				//	data::CELL_SIZE - data::BORDER_CELL * 2,
				//	data::CELL_SIZE - data::BORDER_CELL * 2 };
				//SDL_RenderFillRect(renderer, &rec_insize);
			}
		}
	}
}

bool ManageTetromino::Is_Collision(Tetromino& t) {
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (t.Is_Block(x, y))
			{
				auto wx = t.X()+ x;
				auto wy = t.Y() + y;
				if (wx < 0 || wx >= data::NUM_WIDTH || wy < 0 || wy >= data::NUM_HEIGHT)
					return true;
				if (data[wx][wy]!='0')
					return true;
			}
	return false;
}

void ManageTetromino::Unite(Tetromino& t)
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (t.Is_Block(x, y)) {
				data[t.X() + x][t.Y() + y] = t.Get_Char_Type();
			}
}

int ManageTetromino::Reward(){
	int reward = 0;
	for (int y = data::NUM_HEIGHT - 1; y >= 0; --y)
	{
		bool isReward = true;
		//check hàng có đủ block để ăn hay không
		for (int x = 0; x < data::NUM_WIDTH; ++x)
			if (data[x][y]=='0')
			{
				isReward = false;
				break;
			}
		if (isReward)
		{
			Sound_Reward();
			//tăng điểm
			reward += data::NUM_WIDTH;
			//đẩy các block xuống sau khi ăn hàng block
			for (int yy = y - 1; yy >= 0; --yy)
				for (int x = 0; x < data::NUM_WIDTH; ++x)
					data[x][yy + 1] = data[x][yy];
			//sau khi đẩy thì cho các block trên cùng bằng '0'
			for (int x = 0; x < data::NUM_WIDTH; ++x)
				data[x][0] = '0';
			//sau khi ăn thì reset lại y để set tiếp
			y++;
		}
	}
	return reward;
}

void ManageTetromino::Sound_Reward() {
	Mix_Music* music = Mix_LoadMUS("music_reward.mp3");
	if (music == NULL)
	{
		printf("%s", Mix_GetError());
	}
	Mix_PlayMusic(music, 1);
}