
#ifndef _D34_SDL2_H_
#define _D34_SDL2_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace d34 {
    enum Font
    {
        FONT_TIMES_NEW_ROMAN = 0,
        FONT_ROBUS,
        FONT_GLUE_GUN,
        FONT_STARCRAFT,
    };
    enum Color {
        WHITE=0,
        FIRE_BRICK,
        RED,
        YELLOW,
        GOLD,
        ORANGE,
        BLUE,
        DARK_BLUE,
        DARK_ORCHID,
        PURPLE,
        STEEL_BLUE,
        CORN_FLOWER_BLUE,
        LAWN_GREEN,
        GREEN,
    };

    class D34_SDL2
    {
    public:

        //load mọi định dạng ảnh, giữ nguyên kích cỡ ảnh
        SDL_Surface* Load_Image_SDL_Image(std::string file_path, const SDL_PixelFormat* fomat);

        //load ảnh bmp giũ nguyên kích cỡ của ảnh
        void Load_Image_BMP(SDL_Renderer* renderer, const std::string& file, int x, int y);

        //load ảnh bmp co dãn theo w hà h
        void Load_Image_BMP(SDL_Renderer* renderer, const std::string& file, int x, int y, int w, int h);

        TTF_Font* Convert_Font_To_TTF_Font(Font font, int font_size);

        //khi add color thì phải sửa hàm Convert_Color_To_SDL_Color_RGB(data::Color color)
        SDL_Color Convert_Color_To_SDL_Color_RGB(Color color);
        void D34_SetRenderDrawColor_RGB(SDL_Renderer*, Color);

        //Trả về rect chứa text
        SDL_Rect Load_Text(SDL_Renderer* renderer, const std::string& text, int rec_x, int rec_y, Font font, int font_size, Color color);

        //chuyển đổi key sang kí tự
        char Convert_Key_To_Char(SDL_Keycode key);
    private:
        // Hàm nạp texture từ file ảnh, để vẽ lên renderer tương ứng
        SDL_Texture* Load_Image_BMP_To_Texture(const std::string& file, SDL_Renderer* ren);
        void Free_Texture(SDL_Texture*);
        void Free_TTF_Font(TTF_Font*);
        void Free_Surface(SDL_Surface*);
    };
}
#endif // !_D34_SDL2_H_