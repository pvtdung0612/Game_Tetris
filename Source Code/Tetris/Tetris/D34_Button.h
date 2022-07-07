
#ifndef _D34_BUTTON_H_
#define _D34_BUTTON_H_

#include <iostream>
#include <sdl.h>
#include <sdl_ttf.h>
#include <string>

using namespace std;

namespace d34_btn {
	enum Font
	{
		FONT_TIMES_NEW_ROMAN = 0,
		FONT_ROBUS,
		FONT_GLUE_GUN,
		FONT_STARCRAFT,
	};
	enum Color
	{
		COLOR_RED =0,
		COLOR_YELLOW,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_GRAY,
		COLOR_BLACK,
		COLOR_WHITE,
	};
	enum Horizontal
	{
		HORIZONTAL_NULL = 0,
		HORIZONTAL_LEFT,
		HORIZONTAL_CENTER,
		HORIZONTAL_RIGHT,
	};
	enum Vertical
	{
		VERTICAL_NULL = 0,
		VERTICAL_TOP,
		VERTICAL_CENTER,
		VERTICAL_BOTTOM,
	};

	struct Context
	{
		string text;
		size_t size;
		Font font;
		Color color;
		Horizontal horizontal;
		Vertical vertical;
	};


	//khi set font cho context thì phải set font cho p_context_ttf_font
	//khi load horizontal và vertical cho context thì phải load x va y cho rec_context
	class D34_Button {
	public:
		/*
		padding
		margin
		*/

		D34_Button();
		~D34_Button();

		//coordinate button
		void X(int x);
		int X();
		void Y(int y);
		int Y();

		//dimension button
		void Width(size_t width);
		size_t Width();
		void Height(size_t height);
		size_t Height();

		bool IS_Mouse_In_Button(int mouse_x, int mouse_y );

		void Animation(SDL_Renderer* renderer, int mouse_x, int mouse_y, Color color_before, Color color_after);

		void Sound_Click();

		void Set_Color_Button(Color color);

		void Load_Context(
			string text = "Button",
			Font font = FONT_TIMES_NEW_ROMAN,
			int font_size = 20,
			Color color = COLOR_BLACK,
			Horizontal hor = HORIZONTAL_CENTER,
			Vertical ver = VERTICAL_CENTER
		);
		void Load_Context(
			string text = "Button",
			Font font = FONT_TIMES_NEW_ROMAN,
			int font_size = 20,
			Color color = COLOR_BLACK,
			int padding_left = 0,
			int padding_top = 0
		);
		void Load_Context(const char* text);
		void Load_Context(Font font, int font_size);
		void Load_Context(Horizontal hor, Vertical ver);
		void Load_Context(int padding_left, int padding_top);
		void Load_Context(Color color);

		void Load_Button(SDL_Renderer* renderer);

	private:
		SDL_Rect rec_btn;
		Color btn_color;
		Context context;
		SDL_Rect rec_context;
		TTF_Font* context_ttf_font;

		TTF_Font* Convert_Font_To_TTF_Font(Font font, int font_size);
		SDL_Color Convert_Color_To_SDL_Color(Color color);
		void Convert_Context_Alignment();
		void Free_Texture(SDL_Texture*);
		void Free_TTF_Font(TTF_Font*);
		void Free_Surface(SDL_Surface*);
	};
}

#endif // !_D34_BUTTON_H_