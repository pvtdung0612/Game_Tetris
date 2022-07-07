#ifndef _MANAGE_TETROMINO_H_
#define _MANAGE_TETROMINO_H_

#include <SDL.h>
#include <iostream>
#include "Data.h"
#include "Tetromino.h"
#include "D34_SDL2.h"

using namespace d34;

class ManageTetromino
{
public:
	ManageTetromino();
	~ManageTetromino();

	void Draw(SDL_Renderer* _renderer, D34_SDL2& _D34_SDL2);
	bool Is_Collision(Tetromino&);
	void Unite(Tetromino&);
	int Reward();
	void Sound_Reward();
private:
	const int board_w = 450;
	const int board_h = 600;
	const int board_x = data::BORDER;
	const int board_y = data::BORDER;
	char data[data::NUM_WIDTH][data::NUM_HEIGHT];// chứa các kí tự: 0, I, J, L, O, S, T, Z
};


#endif // !_MANAGE_TETROMINO_H_
