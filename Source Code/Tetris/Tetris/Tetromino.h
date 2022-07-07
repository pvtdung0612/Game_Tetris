#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include <SDL.h>
#include "D34_SDL2.h"
#include "Data.h"

class Tetromino
{
public:
	enum Type { I = 0, J, L, O, S, T, Z, };

	Tetromino(Type);
	~Tetromino();

	void Move(int add_x_, int add_y_);
    void Rotate();
    bool Is_Block(int x, int y);
    void Draw(SDL_Renderer* g_renderer,d34::D34_SDL2& g_D34_sDL2);
    int X();
    int Y();
    char Get_Char_Type();
private:
	int x_; //vị trí ô thứ bao nhiêu trong bơard
	int y_; //vị trí ô thứ bao nhiêu trong bơard
	int angle_; //trạng thái quay
    Type type_; //loại khối
    //lưu thông tin loại khối và trạng thái quay
    const char* Shapes[7][4] = {
        {
          " .  "
          " .  "
          " .  "
          " .  ",
          "    "
          "...."
          "    "
          "    ",
          " .  "
          " .  "
          " .  "
          " .  ",
          "    "
          "...."
          "    "
          "    ",
        },
        {
          "  . "
          "  . "
          " .. "
          "    ",
          "    "
          "    "
          "... "
          "  . ",
          " .. "
          " .  "
          " .  "
          "    ",
          "    "
          ".   "
          "... "
          "    ",
        },
        {
          " .  "
          " .  "
          " .. "
          "    ",
          "  . "
          "... "
          "    "
          "    ",
          " .. "
          "  . "
          "  . "
          "    ",
          "    "
          "... "
          ".   "
          "    ",
        },
        {
          "    "
          " .. "
          " .. "
          "    ",
          "    "
          " .. "
          " .. "
          "    ",
          "    "
          " .. "
          " .. "
          "    ",
          "    "
          " .. "
          " .. "
          "    ",
        },
        {
          "  . "
          " .. "
          " .  "
          "    ",
          "    "
          "..  "
          " .. "
          "    ",
          "  . "
          " .. "
          " .  "
          "    ",
          "    "
          "..  "
          " .. "
          "    ",
        },
        {
          " .  "
          " .. "
          " .  "
          "    ",
          " .  "
          "... "
          "    "
          "    ",
          " .  "
          "..  "
          " .  "
          "    ",
          "    "
          "... "
          " .  "
          "    ",
        },
        {
          " .  "
          " .. "
          "  . "
          "    ",
          "    "
          " .. "
          "..  "
          "    ",
          " .  "
          " .. "
          "  . "
          "    ",
          "    "
          " .. "
          "..  "
          "    ",
        },
    }; 
};


#endif // !_TETROMINO_H_
