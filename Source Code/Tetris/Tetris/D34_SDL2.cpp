#include "D34_SDL2.h"

using namespace d34;

void D34_SDL2::Free_Texture(SDL_Texture* texture) {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
void D34_SDL2::Free_TTF_Font(TTF_Font* ttf_font) {
    if (ttf_font != NULL) {
        TTF_CloseFont(ttf_font);
        ttf_font = NULL;
    }
}
void D34_SDL2::Free_Surface(SDL_Surface* surface) {
    if (surface != NULL) {
        SDL_FreeSurface(surface);
        surface = NULL;
    }
}

SDL_Surface* D34_SDL2::Load_Image_SDL_Image(std::string file_path, const SDL_PixelFormat* format)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(file_path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

SDL_Texture* D34_SDL2::Load_Image_BMP_To_Texture(const std::string& file, SDL_Renderer* ren)
{
    SDL_Texture* texture = nullptr;
    //Nạp ảnh từ tên file (với đường dẫn)
    SDL_Surface* loadedImage = SDL_LoadBMP(file.c_str());
    //Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
    if (loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        Free_Surface(loadedImage);
        //Đảm bảo việc chuyển đổi không có lỗi
        if (texture == nullptr) {
            printf("\nError load bmp");
        }
    }
    else {
        printf("\nError load bmp");
    }
    return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void D34_SDL2::Load_Image_BMP(SDL_Renderer* ren, const std::string& file, int x, int y)
{
    //nạp ảnh vào texture
    SDL_Texture* tex = Load_Image_BMP_To_Texture(file, ren);
    //Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    SDL_RenderCopy(ren, tex, NULL, &dst);
    Free_Texture(tex);
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/

void D34_SDL2::Load_Image_BMP(SDL_Renderer* ren, const std::string& file, int x, int y, int w, int h)
{
    //nạp ảnh vào texture
    SDL_Texture* tex = Load_Image_BMP_To_Texture(file, ren);
    //Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
    SDL_RenderCopy(ren, tex, NULL, &dst);
    Free_Texture(tex);
}

TTF_Font* D34_SDL2::Convert_Font_To_TTF_Font(Font font, int font_size) {
    if (font < 0 || font_size < 0) std::cout << "\nConvert Font in Button Error: ";

    TTF_Font* ttf_font = nullptr;
    std::string path_font = "";

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
SDL_Color D34_SDL2::Convert_Color_To_SDL_Color_RGB(Color color) {
    std::string color_str;

    switch (color) {
    case WHITE:
        color_str = "255255255";
        break;
    case FIRE_BRICK:
        color_str = "255048048";
        break;
    case RED:
        color_str = "255000000";
        break;
    case YELLOW:
        color_str = "255255000";
        break;
    case GOLD:
        color_str = "238201000";
        break;
    case ORANGE:
        color_str = "255165000";
        break;
    case BLUE:
        color_str = "000000255";
        break;
    case DARK_BLUE:
        color_str = "0000000139";
        break;
    case DARK_ORCHID:
        color_str = "154050205";
        break;
    case PURPLE:
        color_str = "128000128";
        break;
    case STEEL_BLUE:
        color_str = "099184255";
        break;
    case CORN_FLOWER_BLUE:
        color_str = "100149237";
        break;
    case LAWN_GREEN:
        color_str = "10225551";
        break;
    case GREEN:
        color_str = "000255000";
        break;
    }

    SDL_Color sdl_color;
    sdl_color.r = ((int)color_str[0] - 48) * 100 + ((int)color_str[1] - 48) * 10 + ((int)color_str[2] - 48);
    sdl_color.g = ((int)color_str[3] - 48) * 100 + ((int)color_str[4] - 48) * 10 + ((int)color_str[5] - 48);
    sdl_color.b = ((int)color_str[6] - 48) * 100 + ((int)color_str[7] - 48) * 10 + ((int)color_str[8] - 48);
    return sdl_color;
}
void D34_SDL2::D34_SetRenderDrawColor_RGB(SDL_Renderer* renderer, Color color) {
    SDL_Color sdl_color = Convert_Color_To_SDL_Color_RGB(color);
    SDL_SetRenderDrawColor(renderer, sdl_color.r, sdl_color.g, sdl_color.b, 255);
}

SDL_Rect D34_SDL2::Load_Text(SDL_Renderer* renderer, const std::string& text, int rec_x, int rec_y, Font font, int font_size, Color color) 
{
    SDL_Rect rect{ 0,0,0,0 };
    if (text == "") return rect;
    SDL_Color sdl_color = Convert_Color_To_SDL_Color_RGB(color);
    TTF_Font* ttf_font = Convert_Font_To_TTF_Font(font, font_size);
    SDL_Surface* surface = TTF_RenderText_Blended(ttf_font, text.c_str(), sdl_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect = SDL_Rect{ rec_x,rec_y,surface->w,surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    Free_TTF_Font(ttf_font);
    Free_Texture(texture);
    return rect;
}

char D34_SDL2::Convert_Key_To_Char(SDL_Keycode key) {
    switch (key)
    {
    case SDLK_0:
       return '0';
    case SDLK_1:
        return '1';
    case SDLK_2:
        return '2';
    case SDLK_3:
        return '3';
    case SDLK_4:
        return '4';
    case SDLK_5:
        return '5';
    case SDLK_6:
        return '6';
    case SDLK_7:
        return '7';
    case SDLK_8:
        return '8';
    case SDLK_9:
        return '9';
    case SDLK_q:
        return 'q';
    case SDLK_w:
        return 'w';
    case SDLK_e:
        return 'e';
    case SDLK_r:
        return 'r';
    case SDLK_t:
        return 't';
    case SDLK_y:
        return 'y';
    case SDLK_u:
        return 'u';
    case SDLK_i:
        return 'i';
    case SDLK_o:
        return 'o';
    case SDLK_p:
        return 'p';
    case SDLK_a:
        return 'a';
    case SDLK_s:
        return 's';
    case SDLK_d:
        return 'd';
    case SDLK_f:
        return 'f';
    case SDLK_g:
        return 'g';
    case SDLK_h:
        return 'h';
    case SDLK_j:
        return 'j';
    case SDLK_k:
        return 'k';
    case SDLK_l:
        return 'l';
    case SDLK_z:
        return 'z';
    case SDLK_x:
        return 'x';
    case SDLK_c:
        return 'c';
    case SDLK_v:
        return 'v';
    case SDLK_b:
        return 'b';
    case SDLK_n:
        return 'n';
    case SDLK_m:
        return 'm';
    default:
        return NULL;
    }
}
//