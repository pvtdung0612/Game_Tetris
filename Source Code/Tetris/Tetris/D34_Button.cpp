#include "D34_Button.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace d34_btn;

D34_Button::D34_Button() {
	X(0);
	Y(0);
	Width(100);
	Height(30);
	Set_Color_Button(COLOR_GRAY);
	Load_Context("Button", FONT_TIMES_NEW_ROMAN, 20, COLOR_BLACK, HORIZONTAL_CENTER, VERTICAL_CENTER);
	context_ttf_font = NULL;
}
D34_Button::~D34_Button() {
}

TTF_Font* D34_Button::Convert_Font_To_TTF_Font(Font font, int font_size) {
	if (font < 0 || font_size < 0) std::cout << "\nConvert Font in Button Error: ";

	TTF_Font* ttf_font = nullptr;
	string path_font = "";

	switch (font) {
	case FONT_TIMES_NEW_ROMAN:
		path_font = "FONT_TIMES_NEW_ROMAN.ttf";
		break;
	case FONT_ROBUS:
		path_font = "FONT_ROBUS.ttf";
		break;
	case FONT_GLUE_GUN:
		path_font = "FONT_GLUE_GUN.ttf";
		break;
	case FONT_STARCRAFT:
		path_font = "FONT_STARCRAFT.ttf";
		break;
	}

	if (path_font == "") {
		std::cout << "\nLoad font error";
	}
	else ttf_font = TTF_OpenFont(path_font.c_str(), font_size);
	return ttf_font;
}

SDL_Color D34_Button::Convert_Color_To_SDL_Color(Color color) {
	if (color < 0) std::cout << "\nConvert Color int Button Error: ";

	SDL_Color sdl_color;

	switch (color) {
	case COLOR_RED:
		sdl_color.r = 255;
		sdl_color.g = 0;
		sdl_color.b = 0;
		sdl_color.a = 255;
		break;
	case COLOR_YELLOW:
		sdl_color.r = 255;
		sdl_color.g = 255;
		sdl_color.b = 0;
		sdl_color.a = 0;
		break;
	case COLOR_BLUE:
		sdl_color.r = 51;
		sdl_color.g = 102;
		sdl_color.b = 255;
		sdl_color.a = 0;
		break;
	case COLOR_GREEN:
		sdl_color.r = 102;
		sdl_color.g = 255;
		sdl_color.b = 51;
		sdl_color.a = 0;
		break;
	case COLOR_GRAY:
		sdl_color.r = 194;
		sdl_color.g = 194;
		sdl_color.b = 163;
		sdl_color.a = 255;
		break;
	case COLOR_BLACK:
		sdl_color.r = 0;
		sdl_color.g = 0;
		sdl_color.b = 0;
		sdl_color.a = 0;
		break;
	case COLOR_WHITE:
		sdl_color.r = 255;
		sdl_color.g = 255;
		sdl_color.b = 255;
		sdl_color.a = 0;
		break;
	}
	return sdl_color;
}

void D34_Button::Convert_Context_Alignment() {

	switch (context.horizontal) {
	case HORIZONTAL_NULL:
		break;
	case HORIZONTAL_LEFT:
		rec_context.x = rec_btn.x;
		break;
	case HORIZONTAL_CENTER:
		rec_context.x = rec_btn.x + (rec_btn.w - rec_context.w) / 2;
		break;
	case HORIZONTAL_RIGHT:
		rec_context.x = rec_btn.x + rec_btn.w - rec_context.w;
		break;
	}

	switch (context.vertical) {
	case VERTICAL_NULL:
		break;
	case VERTICAL_TOP:
		rec_context.y = rec_btn.y;
		break;
	case VERTICAL_CENTER:
		rec_context.y = rec_btn.y + (rec_btn.h - rec_context.h) / 2;
		break;
	case VERTICAL_BOTTOM:
		rec_context.y = rec_btn.y + rec_btn.h - rec_context.h;
		break;
	}
}

//coordinate button
void D34_Button::X(int x) {
	this->rec_btn.x = x;
}
int D34_Button::X() {
	return rec_btn.x;
}
void D34_Button::Y(int y) {
	this->rec_btn.y = y;
}
int D34_Button::Y() {
	return rec_btn.y;
}

//dimension button
void D34_Button::Width(size_t w) {
	this->rec_btn.w = w;
}
size_t D34_Button::Width() {
	return rec_btn.w;
}
void D34_Button::Height(size_t h) {
	this->rec_btn.h = h;
}
size_t D34_Button::Height() {
	return rec_btn.h;
}

bool D34_Button::IS_Mouse_In_Button(int mouse_x, int mouse_y ) {
	if (mouse_x >= rec_btn.x && mouse_x <= rec_btn.x + rec_btn.w
		&& mouse_y >= rec_btn.y && mouse_y <= rec_btn.y + rec_btn.h) return true;
	else return false;
}

void D34_Button::Animation(SDL_Renderer* renderer, int mouse_x, int mouse_y, Color text_color_before, Color text_color_after) {
	if (this->IS_Mouse_In_Button(mouse_x,mouse_y))
		this->Load_Context(d34_btn::COLOR_RED);
	else
		this->Load_Context(d34_btn::COLOR_WHITE);
}

void D34_Button::Sound_Click() {
	Mix_Music* music = Mix_LoadMUS("music_button_click.mp3");
	if (music == NULL)
	{
		printf("%s", Mix_GetError());
	}
	Mix_PlayMusic(music, 1);
}

void D34_Button::Set_Color_Button(Color color) {
	btn_color = color;
}

/// <summary>
/// LOAD_CONTEXT
/// </summary>
/// <param name="text"></param>
/// <param name="font"></param>
/// <param name="font_size"></param>
/// <param name="color"></param>
/// <param name="hor"></param>
/// <param name="ver"></param>
void D34_Button::Load_Context(
	string text,
	Font font,
	int font_size,
	Color color,
	Horizontal hor,
	Vertical ver) {
	context.text = text;
	context.font = font;
	Convert_Font_To_TTF_Font(font, font_size);
	context.size = font_size;
	context.color = color;
	context.horizontal = hor;
	context.vertical = ver;
}
void D34_Button::Load_Context(
	string text,
	Font font,
	int font_size,
	Color color,
	int padding_left,
	int padding_top
) {
	context.text = text;
	context.font = font;
	Convert_Font_To_TTF_Font(font, font_size);
	context.size = font_size;
	context.color = color;
	rec_context.x = padding_left + rec_btn.x;
	rec_context.y = padding_top + rec_btn.y;
}
void D34_Button::Load_Context(const char* text) {
	context.text = text;
}
void D34_Button::Load_Context(Font font, int font_size) {
	context.font = font;
	context.size = font_size;
	Convert_Font_To_TTF_Font(font, font_size);
}
void D34_Button::Load_Context(Horizontal hor, Vertical ver){
	context.horizontal = hor;
	context.vertical = ver;
}
void D34_Button::Load_Context(int padding_left, int padding_top) {
	rec_context.x = rec_btn.x + padding_left;
	rec_context.y = rec_btn.y + padding_top;
}
void D34_Button::Load_Context(Color color) {
	context.color = color;
}
void D34_Button::Load_Button(SDL_Renderer* renderer) {
	//draw button
	SDL_Color sdl_btn_color = Convert_Color_To_SDL_Color(btn_color);
	SDL_SetRenderDrawColor(renderer, sdl_btn_color.r, sdl_btn_color.g, sdl_btn_color.b, sdl_btn_color.a);
	SDL_RenderFillRect(renderer, &rec_btn);

	//draw context
	//convert font, text, color
	Free_TTF_Font(context_ttf_font);
    context_ttf_font = Convert_Font_To_TTF_Font(context.font, context.size);
	SDL_Color sdl_context_color = Convert_Color_To_SDL_Color(context.color);
	SDL_SetRenderDrawColor(renderer, sdl_context_color.r, sdl_context_color.g, sdl_context_color.b, sdl_context_color.a);
	if (context.text == "") context.text = "Button";
	SDL_Surface* surface = TTF_RenderText_Blended(context_ttf_font, context.text.c_str(), sdl_context_color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	rec_context.w = surface->w;
	rec_context.h = surface->h;
	Free_Surface(surface);
	//convert horizontal, vertical
	Convert_Context_Alignment();
	SDL_RenderCopy(renderer, texture, NULL, &rec_context);
	//std::cout << "\nLoaded a button, text: " << context.text;

	Free_Texture(texture);
}

void D34_Button::Free_Texture(SDL_Texture* texture) {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}
void D34_Button::Free_TTF_Font(TTF_Font* ttf_font) {
	if (ttf_font != NULL) {
		TTF_CloseFont(ttf_font);
		ttf_font = NULL;
	}
}
void D34_Button::Free_Surface(SDL_Surface* surface) {
	if (surface != NULL) {
		SDL_FreeSurface(surface);
		surface = NULL;
	}
}