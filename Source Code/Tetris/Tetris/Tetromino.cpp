#include "Tetromino.h"
#include "ManageTetromino.h"

Tetromino::Tetromino(Type type) {
	type_ = type;
	x_ = 6;
	y_ = 0;
	angle_ = 0;
}
Tetromino::~Tetromino() {}
void Tetromino::Draw(SDL_Renderer* g_renderer,D34_SDL2& g_D34_SDL2)
{
	for (auto x = 0; x < 4; ++x)
		for (auto y = 0; y < 4; ++y)
			if (Is_Block(x, y))
			{
				switch (type_) {
				case I:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_light_blue.bmp", (x + x_) * data::CELL_SIZE + data::BORDER,(y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case J:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_orange.bmp", (x + x_) * data::CELL_SIZE + data::BORDER, (y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case L:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_blue.bmp", (x + x_) * data::CELL_SIZE + data::BORDER, (y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case O:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_yellow.bmp", (x + x_) * data::CELL_SIZE + data::BORDER, (y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case S:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_green.bmp", (x + x_) * data::CELL_SIZE + data::BORDER, (y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case T:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_purple.bmp", (x + x_) * data::CELL_SIZE + data::BORDER, (y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				case Z:
					g_D34_SDL2.Load_Image_BMP(g_renderer, "Block_red.bmp", (x + x_) * data::CELL_SIZE + data::BORDER, (y + y_) * data::CELL_SIZE + data::BORDER, data::CELL_SIZE, data::CELL_SIZE);
					break;
				}

				/*SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
				SDL_Rect rec_outsize{
					(x + x_) * data::CELL_SIZE + data::BORDER,
					(y + y_) * data::CELL_SIZE + data::BORDER,
					data::CELL_SIZE,
					data::CELL_SIZE };
				SDL_RenderFillRect(renderer, &rec_outsize);*/

				//SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
				//SDL_Rect rec_insize{
				//	(x+x_) * data::CELL_SIZE + data::BORDER + data::BORDER_CELL,
				//	(y+y_) * data::CELL_SIZE + data::BORDER + data::BORDER_CELL,
				//	data::CELL_SIZE - data::BORDER_CELL * 2,
				//	data::CELL_SIZE - data::BORDER_CELL * 2 };
				//SDL_RenderFillRect(renderer, &rec_insize);
			}
}
void Tetromino::Move(int add_x_, int add_y_) {
    x_ += add_x_;
    y_ += add_y_;
}
void Tetromino::Rotate()
{
	angle_ += 3;
	angle_ %= 4;
}
bool Tetromino::Is_Block(int x, int y) 
{
    return Shapes[type_][angle_][x + y * 4] == '.';
}
int Tetromino::X()
{
	return x_;
}
int Tetromino::Y()
{
	return y_;
}
char Tetromino::Get_Char_Type() {
	if (type_ == I) return 'I';
	if (type_ == J) return 'J';
	if (type_ == L) return 'L';
	if (type_ == O) return 'O';
	if (type_ == S) return 'S';
	if (type_ == T) return 'T';
	if (type_ == Z) return 'Z';
}

