
#include "LaunchPlay.h"
#include "ManageTetromino.h"
#include "Tetromino.h"
#include <fstream>
#include <ctime>
#include <SDL_mixer.h>

using namespace data;
using namespace std;

LaunchPlay::LaunchPlay(SDL_Renderer* _g_renderer, D34_SDL2& _g_D34_SDL2):
    tetromino_ {static_cast<Tetromino::Type>(rand() % 7)}
{
    //tetromino_ = Tetromino{ static_cast<Tetromino::Type>(rand() % 7) };
    srand(time(NULL));
    g_renderer = _g_renderer;
    g_D34_SDL2 = _g_D34_SDL2;

    player.name = "Player";
    player.mark = 0;
    player.level = 1;
    player.num_block = 1;
    player.time_play = 0.0;

    speed=data::level1::speed;

    ifstream rf("Hight_score.txt", ios::in);
    if (!rf) cout << "\nCannot open file!";
    string str_temp = "";
    rf >> str_temp;
    rf >> hight_mark;
    rf.close();
    if (!rf.good()) cout << "\nError occurred at reading time!";

    btn_exit.Load_Context("Exit");
    btn_exit.Load_Context(d34_btn::FONT_STARCRAFT, 25);
    btn_exit.Load_Context(d34_btn::COLOR_WHITE);
    btn_exit.Set_Color_Button(d34_btn::COLOR_BLUE);
    btn_exit.Width(200);
    btn_exit.Height(50);
    btn_exit.X(480);
    btn_exit.Y(SCREEN_HEIGHT - BORDER - btn_exit.Height() - 10);
}

LaunchPlay::~LaunchPlay() {}

bool LaunchPlay::Enter_Name() {
    bool success = true;
    bool isRun = true;
    player.name = "_";
    SDL_Event e; 
  
    //Text Hint
    SDL_Rect rec_hint = g_D34_SDL2.Load_Text(g_renderer, "Enter your name", 0, -100, d34::FONT_STARCRAFT, 25, d34::WHITE);
    rec_hint.x = (data::SCREEN_WIDTH - rec_hint.w) / 2;
    rec_hint.y = 200;
 
    //Text name
    SDL_Rect rec_name = g_D34_SDL2.Load_Text(g_renderer, player.name, 0, 0, d34::FONT_STARCRAFT, 25, d34::WHITE);
    rec_name.y = rec_hint.y + rec_hint.h + 20;
 
    //Button OK
    d34_btn::D34_Button btn_ok;      
    btn_ok.Load_Context("OK");
    btn_ok.Load_Context(d34_btn::FONT_STARCRAFT, 25);
    btn_ok.Load_Context(d34_btn::COLOR_WHITE);
    btn_ok.Set_Color_Button(d34_btn::COLOR_BLUE);
    btn_ok.Width(200);
    btn_ok.Height(50);
    btn_ok.X((SCREEN_WIDTH - btn_ok.Width()) / 2);
    btn_ok.Y(rec_name.y + rec_name.h + 20);
    
    //Main loop
    while (isRun)
    {
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
        SDL_RenderClear(g_renderer);

        //Text Hint
        rec_hint = g_D34_SDL2.Load_Text(g_renderer, "Enter your name", rec_hint.x, rec_hint.y, d34::FONT_STARCRAFT, 25, d34::WHITE);

        //Text Name
        rec_name.x = (data::SCREEN_WIDTH - rec_name.w) / 2;
        rec_name = g_D34_SDL2.Load_Text(g_renderer, player.name, rec_name.x, rec_name.y, d34::FONT_STARCRAFT, 25, d34::WHITE);

        //Button OK
        btn_ok.Load_Button(g_renderer);

        SDL_RenderPresent(g_renderer);

        SDL_WaitEvent(&e);
        switch (e.type) {
        case SDL_KEYDOWN:
            Sound_KeyBoard();
            player.name.pop_back();
            switch (e.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                if (player.name.size() > 0)
                    player.name.pop_back();
                break;
            case SDLK_RETURN: //phim enter
                isRun = false;
                break;
            default:
                if (player.name.size()<=14 && g_D34_SDL2.Convert_Key_To_Char(e.key.keysym.sym) != NULL) {
                    player.name += g_D34_SDL2.Convert_Key_To_Char(e.key.keysym.sym);
                }
                break;
            }
            player.name += "_";
            cout << "\n" << player.name;
            cout << "\n" << player.name.size();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (btn_ok.IS_Mouse_In_Button(e.button.x, e.button.y)) {
                btn_ok.Sound_Click();
                success = true;
                isRun = false;
            }
            break;
        case SDL_QUIT:
            success = false;
            isRun = false;
            break;
        }
    }

    if (player.name == "_" || player.name == "") player.name = "Player";
    else player.name.pop_back();
    return success;
}

bool LaunchPlay::Run() {
    //chỉ xét va chạm khi block tự rơi xuống còn dùng sự kiện thì vẫn không xét va chạm
    SDL_Event e;
    bool isRun = true;
    bool isLost = false;
    isRun = Enter_Name();
    time_start = clock();
    player.time_play = 0;
    Sound_Play();

    //Main loop
    while (isRun) {
        //EVENT ///////////////////////////////////////////////////////////////////////
        //Event chỉ thay đổi tọa độ Tetromino không có chức năng khác
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                if (btn_exit.IS_Mouse_In_Button(e.button.x, e.button.y))
                    btn_exit.Load_Context(d34_btn::COLOR_RED);
                else
                    btn_exit.Load_Context(d34_btn::COLOR_WHITE);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (btn_exit.IS_Mouse_In_Button(e.button.x, e.button.y)) 
                {
                    btn_exit.Sound_Click();
                    isRun = false;
                }
                break;
            case SDL_KEYDOWN:
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_DOWN:
                {
                    Tetromino t = tetromino_;
                    t.Move(0, 1);
                    if (!manage_.Is_Collision(t))
                        tetromino_ = t;
                }
                break;
                case SDLK_RIGHT:
                {
                    Tetromino t = tetromino_;
                    t.Move(1, 0);
                    if (!manage_.Is_Collision(t))
                        tetromino_ = t;
                }
                break;
                case SDLK_LEFT:
                {
                    Tetromino t = tetromino_;
                    t.Move(-1, 0);
                    if (!manage_.Is_Collision(t))
                        tetromino_ = t;
                }
                break;
                case SDLK_UP:
                {
                    Tetromino t = tetromino_;
                    t.Rotate();
                    if (!manage_.Is_Collision(t))
                        tetromino_ = t;
                }
                break;
                }
            }
            break;
            case SDL_QUIT:
                isRun = false;
                break;
            }
        }

        //LOAD SCREEN ////////////////////////////////////////////////////////////
        g_D34_SDL2.D34_SetRenderDrawColor_RGB(g_renderer, BLUE);
        SDL_RenderClear(g_renderer);
        //load board
        manage_.Draw(g_renderer, g_D34_SDL2);
        tetromino_.Draw(g_renderer, g_D34_SDL2);
        //load information
        {
            //background
            SDL_Rect rec_info{ BORDER * 2 + BOARD_BLOCK_WIDTH,BORDER,SCREEN_WIDTH - BORDER * 3 - BOARD_BLOCK_WIDTH,SCREEN_HEIGHT - BORDER * 2 };
            SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(g_renderer, &rec_info);
            //Hight Mark
            if (hight_mark > 9999) hight_mark = 9999;
            if (hight_mark < player.mark) hight_mark = player.mark;
            g_D34_SDL2.Load_Text(g_renderer, "Highest: " + to_string(hight_mark),
                BORDER * 3 + BOARD_BLOCK_WIDTH,
                BORDER * 2, FONT_GLUE_GUN, 40, WHITE);
            //Mark
            if (player.mark > 99999) player.mark = 99999;
            g_D34_SDL2.Load_Text(g_renderer, "Mark: " + to_string(player.mark),
                BORDER * 3 + BOARD_BLOCK_WIDTH,
                BORDER * 2 + 60, FONT_GLUE_GUN, 40, WHITE);
            //Level
            if (player.mark < level1::mark) {
                speed = level1::speed;
                g_D34_SDL2.Load_Text(g_renderer, "Level: 1",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 120, FONT_GLUE_GUN, 40, WHITE);
            }
            else if (player.mark < level2::mark) {
                speed = level2::speed;
                g_D34_SDL2.Load_Text(g_renderer, "Level: 2",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 120, FONT_GLUE_GUN, 40, WHITE);
            }
            else if (player.mark < level3::mark) {
                speed = level3::speed;
                g_D34_SDL2.Load_Text(g_renderer, "Level: 3",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 120, FONT_GLUE_GUN, 40, WHITE);
            }
            else if (player.mark < level4::mark) {
                speed = level4::speed;
                g_D34_SDL2.Load_Text(g_renderer, "Level: 4",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 120, FONT_GLUE_GUN, 40, WHITE);
            }
            else if (player.mark < level5::mark) {
                speed = level5::speed;
                g_D34_SDL2.Load_Text(g_renderer, "Level: 5",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 120, FONT_GLUE_GUN, 40, WHITE);
            }
            else {
                speed = level6::speed;
                g_D34_SDL2.Load_Text(g_renderer, "Level: Max",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 120, FONT_GLUE_GUN, 40, WHITE);
            }
            //Block
            g_D34_SDL2.Load_Text(g_renderer, "Block: " + to_string(player.num_block),
                BORDER * 3 + BOARD_BLOCK_WIDTH,
                BORDER * 2 + 180, FONT_GLUE_GUN, 40, WHITE);
            //Time
            if (player.time_play > 99999)
                g_D34_SDL2.Load_Text(g_renderer, "Time: " + to_string(99999) + "s",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 180, FONT_GLUE_GUN, 40, WHITE);
            else {
                string strtime = to_string(player.time_play);
                strtime = strtime.substr(0, strtime.find('.', 0) + 2);
                g_D34_SDL2.Load_Text(g_renderer, "Time: " + strtime + "s",
                    BORDER * 3 + BOARD_BLOCK_WIDTH,
                    BORDER * 2 + 240, FONT_GLUE_GUN, 40, WHITE);
            }
            //Exit Button
            btn_exit.Load_Button(g_renderer);
        }

        //TETROMINO RƠI TỰ DO //////////////////////////////////////////////////////
        if (((double)(clock()-time_start))/1000 > player.time_play)
        {
            player.time_play+=speed;
            //tạo tetromino mới để xét collision
            Tetromino t = tetromino_;
            t.Move(0, 1);
            //khi tetromino vừa tạo ra collíion với tetromino khác thì unite tetromino_ nếu không thì tetromino vừa tạo ra gán cho tetromino_ 
            if (manage_.Is_Collision(t))
            {
                player.num_block++;
                manage_.Unite(tetromino_);
                player.mark += manage_.Reward();
                tetromino_ = Tetromino{ static_cast<Tetromino::Type>(rand() % 7) };
                if (manage_.Is_Collision(tetromino_))
                {
                    isRun = false;
                    isLost = true;
                }
            }
            else
            {
                tetromino_ = t;
            }
        }

        //DRAW /////////////////////////////////////////////////////////////////////
        SDL_RenderPresent(g_renderer);
    }

    Save_Info_Player();
    //Lost
    Mix_HaltChannel(-1);
    if (isLost) Lost();
    return true;
}

void LaunchPlay::Save_Info_Player() {
        //cập nhật thông tin người chơi
            //level
        if (speed == 1) player.level = 1;
        else if (speed == 0.8) player.level = 2;
        else if (speed == 0.6) player.level = 3;
        else if (speed == 0.4) player.level = 4;
        else if (speed == 0.2) player.level = 5;
        else if (speed == 0.1) player.level = 6;

        Info_Player ary_player[NUM_HIGHT_SCORE + 1];

        //gán NUM_HIGHT_SCORE + 1 người chơi vào mảng
        ary_player[NUM_HIGHT_SCORE] = player; //gán info player hiện tại vào cuối mảng
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

        //sắp xếp
        for (int i = 0; i < NUM_HIGHT_SCORE + 1 - 1; i++)
        {
            for (int j = 0; j < NUM_HIGHT_SCORE + 1 - 1 - i; j++)
            {
                Info_Player swap_temp;
                if (ary_player[j].mark < ary_player[j + 1].mark) {//so sánh mark trước
                    swap_temp = ary_player[j];
                    ary_player[j] = ary_player[j + 1];
                    ary_player[j + 1] = swap_temp;
                }
                else if (ary_player[j].mark == ary_player[j + 1].mark) {//nếu mark bằng nhau
                    if (ary_player[j].num_block < ary_player[j + 1].num_block) {//so sánh num_block
                        swap_temp = ary_player[j];
                        ary_player[j] = ary_player[j + 1];
                        ary_player[j + 1] = swap_temp;
                    }
                    else if (ary_player[j].num_block == ary_player[j + 1].num_block) {//nếu num_block bằng nhau
                        if (ary_player[j].time_play < ary_player[j + 1].time_play) {//so sánh time_play
                            swap_temp = ary_player[j];
                            ary_player[j] = ary_player[j + 1];
                            ary_player[j + 1] = swap_temp;
                        }
                    }
                }
            }
        }

        //lưu mảng có NUM_HIGHT_SCORE phần tử vào file
        ofstream wf("hight_score.txt", ios::out);
        for (int i = 0; i < NUM_HIGHT_SCORE; i++)
        {
            if (ary_player[i].num_block > 0 && ary_player[i].mark >= 0 && ary_player[i].level > 0) {
                if (ary_player[i].name == "") ary_player[i].name = "Player";
                wf << ary_player[i].name << " ";
                wf << ary_player[i].mark << " ";
                wf << ary_player[i].level << " ";
                wf << ary_player[i].num_block << " ";

                //xử lý lưu kiểu double 1 số sau dấu phẩy cho time_play
                string strtime = to_string(ary_player[i].time_play);
                strtime = strtime.substr(0, strtime.find('.', 0) + 2);
                wf << strtime << " ";
            }
        }
        wf.close();
}

void LaunchPlay::Lost() {
    Sound_Lost();
    SDL_RenderClear(g_renderer);
    g_D34_SDL2.Load_Image_BMP(g_renderer, "Lost_background.bmp", 0, 0, data::SCREEN_WIDTH, data::SCREEN_HEIGHT);
    SDL_RenderPresent(g_renderer);

    bool exit = false;
    SDL_Event e;
    while (!exit)
    {
        if (SDL_WaitEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT)
                exit = true;

        }
    }

    Mix_HaltMusic();
}

void LaunchPlay::Sound_Play() {
    Mix_Chunk* sound_play = Mix_LoadWAV("music_play.wav");
    if (sound_play == NULL)
    {
        printf("%s", Mix_GetError());
    }
    Mix_PlayChannel(-1, sound_play, -1);
}

void LaunchPlay::Sound_KeyBoard() {
    Mix_Music* music = Mix_LoadMUS("music_keyboard2.mp3");
    if (music == NULL)
    {
        printf("%s", Mix_GetError());
    }
    Mix_PlayMusic(music, 1);
}

void LaunchPlay::Sound_Lost() {
    Mix_Music* music = Mix_LoadMUS("music_lost.mp3");
    if (music == NULL)
    {
        printf("%s", Mix_GetError());
    }
    Mix_PlayMusic(music, 1);
}