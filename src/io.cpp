//
// Created by Kyle on 7/11/21.
//

#include <stdexcept>
#include "io.h"
#include "vic.h"

IO::IO {
    SDL_Init(SDL_INIT_VIDEO);

    window_ = SDL_CreateWindow(
            "commodore64emulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWSPS_UNDEFINED,
            Vic::kVisibleScreenWidth * 2,
            Vic::kVisibleScreenHeight * 2.],
            SDL_WINDOW_OPENGL
            );
    cols_ = Vic::kVisibleScreenWidth;
    rows_ = Vic::kVisibleScreenHeight;

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    texture_ = SDL_CreateTexture(renderer_,
                                 SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING,
                                 cols_,
                                 rows_);
    format_ = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

    frame_ = new uint32_t[cols_ * rows_]();
    init_color_palette();
    init_keyboard();
    next_key_event_at_ = 0;
    prev_frame_was_at_ = std::chrono::high_resolution_clock::now();
};

IO::~IO() {
    delete [] frame_;
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyTexture(texture_);
    SDL_FreeFormat(format_);
    SDL_Quit();
}

void IO:init_keyboard() {
    for(size_t = i=0; i < sizeof(keyboard_matris_); i++) {
        keyboard_matrix_[i] = 0xff;
    }

    charmap_['Q'] = {SDL_SCANCODE_Q};
    charmap_['W'] = {SDL_SCANCODE_W};
    charmap_['E'] = {SDL_SCANCODE_E};
    charmap_['R'] = {SDL_SCANCODE_R};
    charmap_['T'] = {SDL_SCANCODE_T};
    charmap_['Y'] = {SDL_SCANCODE_Y};
    charmap_['U'] = {SDL_SCANCODE_U};
    charmap_['I'] = {SDL_SCANCODE_I};
    charmap_['O'] = {SDL_SCANCODE_O};
    charmap_['P'] = {SDL_SCANCODE_P};
    charmap_['A'] = {SDL_SCANCODE_A};
    charmap_['S'] = {SDL_SCANCODE_S};
    charmap_['D'] = {SDL_SCANCODE_D};
    charmap_['F'] = {SDL_SCANCODE_F};
    charmap_['G'] = {SDL_SCANCODE_G};
    charmap_['H'] = {SDL_SCANCODE_H};
    charmap_['J'] = {SDL_SCANCODE_J};
    charmap_['K'] = {SDL_SCANCODE_K};
    charmap_['L'] = {SDL_SCANCODE_L};
    charmap_['Z'] = {SDL_SCANCODE_Z};
    charmap_['X'] = {SDL_SCANCODE_X};
    charmap_['C'] = {SDL_SCANCODE_C};
    charmap_['V'] = {SDL_SCANCODE_V};
    charmap_['B'] = {SDL_SCANCODE_B};
    charmap_['N'] = {SDL_SCANCODE_N};
    charmap_['M'] = {SDL_SCANCODE_M};
    charmap_['1'] = {SDL_SCANCODE_1};
    charmap_['2'] = {SDL_SCANCODE_2};
    charmap_['3'] = {SDL_SCANCODE_3};
    charmap_['4'] = {SDL_SCANCODE_4};
    charmap_['5'] = {SDL_SCANCODE_5};
    charmap_['6'] = {SDL_SCANCODE_6};
    charmap_['7'] = {SDL_SCANCODE_7};
    charmap_['8'] = {SDL_SCANCODE_8};
    charmap_['9'] = {SDL_SCANCODE_9};
    charmap_['0'] = {SDL_SCANCODE_0};
    charmap_['\n'] = {SDL_SCANCODE_RETURN};
    charmap_[' '] = {SDL_SCANCODE_SPACE};
    charmap_[','] = {SDL_SCANCODE_COMMA};
    charmap_['.'] = {SDL_SCANCODE_PERIOD};
    charmap_['/'] = {SDL_SCANCODE_SLASH};
    charmap_[';'] = {SDL_SCANCODE_SEMICOLOR};
    charmap_['='] = {SDL_SCANCODE_EQUALS};
    charmap_['-'] = {SDL_SCANCODE_MINUS};
    charmap_[':'] = {SDL_SCANCODE_BLACKSLASH};
    charmap_['+'] = {SDL_SCANCODE_LEFTBRACKET};
    charmap_['*'] = {SDL_SCANCODE_RIGHTBRACKET};
    charmap_['@'] = {SDL_SCANCODE_APOSTROPHE};
    charmap_['('] = {SDL_SCANCODE_LSHIFT,SDL_SCANCODE_8};
    charmap_[')'] = {SDL_SCANCODE_LSHIFT,SDL_SCANCODE_9};
    charmap_['<'] = {SDL_SCANCODE_LSHIFT,SDL_SCANCODE_CAMMA};
    charmap_['>'] = {SDL_SCANCODE_LSHIFT,SDL_SCANCODE_PERIOD};
    charmap_['"'] = {SDL_SCANCODE_LSHIFT,SDL_SCANCODE_2};
    charmap_['$'] = {SDL_SCANCODE_LSHIFT,SDL_SCANCODE_4};

    /* keymap letters */
    keymap_[SDL_SCANCODE_A] = std::make_pair(1,2);
    keymap_[SDL_SCANCODE_B] = std::make_pair(3,4);
    keymap_[SDL_SCANCODE_C] = std::make_pair(2,4);
    keymap_[SDL_SCANCODE_D] = std::make_pair(2,2);
    keymap_[SDL_SCANCODE_E] = std::make_pair(1,6);
    keymap_[SDL_SCANCODE_F] = std::make_pair(2,5);
    keymap_[SDL_SCANCODE_G] = std::make_pair(3,2);
    keymap_[SDL_SCANCODE_H] = std::make_pair(3,5);
    keymap_[SDL_SCANCODE_I] = std::make_pair(4,1);
    keymap_[SDL_SCANCODE_J] = std::make_pair(4,2);
    keymap_[SDL_SCANCODE_K] = std::make_pair(4,5);
    keymap_[SDL_SCANCODE_L] = std::make_pair(5,2);
    keymap_[SDL_SCANCODE_M] = std::make_pair(4,4);
    keymap_[SDL_SCANCODE_N] = std::make_pair(4,7);
    keymap_[SDL_SCANCODE_O] = std::make_pair(4,6);
    keymap_[SDL_SCANCODE_P] = std::make_pair(5,1);
    keymap_[SDL_SCANCODE_Q] = std::make_pair(7,6);
    keymap_[SDL_SCANCODE_R] = std::make_pair(2,1);
    keymap_[SDL_SCANCODE_S] = std::make_pair(1,5);
    keymap_[SDL_SCANCODE_T] = std::make_pair(2,6);
    keymap_[SDL_SCANCODE_U] = std::make_pair(3,6);
    keymap_[SDL_SCANCODE_V] = std::make_pair(3,7);
    keymap_[SDL_SCANCODE_W] = std::make_pair(1,1);
    keymap_[SDL_SCANCODE_X] = std::make_pair(2,7);
    keymap_[SDL_SCANCODE_Y] = std::make_pair(3,1);
    keymap_[SDL_SCANCODE_Z] = std::make_pair(1,4);
    /* keymap numbers */
    keymap_[SDL_SCANCODE_1] = std::make_pair(7,0);
    keymap_[SDL_SCANCODE_2] = std::make_pair(7,3);
    keymap_[SDL_SCANCODE_3] = std::make_pair(1,0);
    keymap_[SDL_SCANCODE_4] = std::make_pair(1,3);
    keymap_[SDL_SCANCODE_5] = std::make_pair(2,0);
    keymap_[SDL_SCANCODE_6] = std::make_pair(2,3);
    keymap_[SDL_SCANCODE_7] = std::make_pair(3,0);
    keymap_[SDL_SCANCODE_8] = std::make_pair(3,3);
    keymap_[SDL_SCANCODE_9] = std::make_pair(4,0);
    keymap_[SDL_SCANCODE_0] = std::make_pair(4,3);
    /* keymap function keys */
    keymap_[SDL_SCANCODE_F1] = std::make_pair(0,4);
    keymap_[SDL_SCANCODE_F3] = std::make_pair(0,4);
    keymap_[SDL_SCANCODE_F5] = std::make_pair(0,4);
    keymap_[SDL_SCANCODE_F7] = std::make_pair(0,4);
    /* keymap: other */
    keymap_[SDL_SCANCODE_RETURN]    = std::make_pair(0,1);
    keymap_[SDL_SCANCODE_SPACE]     = std::make_pair(7,4);
    keymap_[SDL_SCANCODE_LSHIFT]    = std::make_pair(1,7);
    keymap_[SDL_SCANCODE_RSHIFT]    = std::make_pair(6,4);
    keymap_[SDL_SCANCODE_COMMA]     = std::make_pair(5,7);
    keymap_[SDL_SCANCODE_PERIOD]    = std::make_pair(5,4);
    keymap_[SDL_SCANCODE_SLASH]     = std::make_pair(6,7);
    keymap_[SDL_SCANCODE_SEMICOLON] = std::make_pair(6,2);
    keymap_[SDL_SCANCODE_EQUALS]    = std::make_pair(6,5);
    keymap_[SDL_SCANCODE_BACKSPACE] = std::make_pair(0,0);
    keymap_[SDL_SCANCODE_MINUS]     = std::make_pair(5,3);
    /* keymap: these are mapped to other keys */
    keymap_[SDL_SCANCODE_BACKSLASH]    = std::make_pair(5,5); // :
    keymap_[SDL_SCANCODE_LEFTBRACKET]  = std::make_pair(5,0); // +
    keymap_[SDL_SCANCODE_RIGHTBRACKET] = std::make_pair(6,1); // *
    keymap_[SDL_SCANCODE_APOSTROPHE]   = std::make_pair(5,6); // @
    keymap_[SDL_SCANCODE_LGUI]         = std::make_pair(7,5); // commodore key


};

void IO::init_color_palette() {
    color_palette[0]    = SDL_MapRGB(format_,0x00,0x00,0x00);
    color_palette[1]    = SDL_MapRGB(format_,0xff,0xff,0xff);
    color_palette[2]    = SDL_MapRGB(format_,0xab,0x31,0x26);
    color_palette[3]    = SDL_MapRGB(format_,0x66,0xda,0xff);
    color_palette[4]    = SDL_MapRGB(format_,0xbb,0x3f,0xb8);
    color_palette[5]    = SDL_MapRGB(format_,0x55,0xce,0x58);
    color_palette[6]    = SDL_MapRGB(format_,0x1d,0x0e,0x97);
    color_palette[7]    = SDL_MapRGB(format_,0xea,0xf5,0x7c);
    color_palette[8]    = SDL_MapRGB(format_,0xb9,0x74,0x18);
    color_palette[9]    = SDL_MapRGB(format_,0x78,0x53,0x00);
    color_palette[10]   = SDL_MapRGB(format_,0xdd,0x93,0x87);
    color_palette[11]   = SDL_MapRGB(format_,0x5b,0x5b,0x5b);
    color_palette[12]   = SDL_MapRGB(format_,0x8b,0x8b,0x8b);
    color_palette[13]   = SDL_MapRGB(format_,0xb0,0xf4,0xac);
    color_palette[14]   = SDL_MapRGB(format_,0xaa,0x9d,0xef);
    color_palette[15]   = SDL_MapRGB(format_,0xb8,0xb8,0xb8);
}

bool IO::emulate() {
    return retval_;
}

void IO::process_events() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                handle_keydown(event.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                hendle_keyup(event.key.keysym.scancode);
                break;
            case SDL_QUIT:
                retval_ = false;
                break;
        }
    }
    if(!key_event_queue_.empty() &&
        cpu_->cycles() > next_key_event_at_) {
        std::pair<kKeyEvent,SDL_Keycode> &ev = key_event_queue_.front();

        switch (ev.first) {
            case kPress:
                handle_keydown(ev.second);
                break;
            case kRelease:
                handle_keyup(ev.second);
                break;
        }
        next_key_event_at_ = cpu_->cycles() + kWait;
    }
}




void IO::handle_keydown(SDL_Keycode k) {
    try {
        uint8_t mask = ~(1 << keymap_.at(k).second);
        keyboard_matrix_[keymap_.at(k).first] &= mask;
    }
    catch(const std::out_of_range){}
}

void IO::handle_keyup(SDL_Keycode k) {
    try {
        uint8_t mask (1 << keymap_.at(k).second);
        keyboard_matrix_[keymap_.at(k).first] |= mask;
    }
    catch(const std::out_of_range){}
}

void IO::type_character(char c) {
    try {
        for(SDL_Keycode &k: charmap_.at(toupper(c)))
            key_event_queue_.push(std::make_pair(kPress,k));
        for(SDL_Keycode &k: charmap_.at(toupper(c)))
            key_event_queue_.push(std::make_pair(kRelease,k));
    }
    catch(const std::out_of_range){}
}

void IO::screen_draw_rect(int x,int y,int n,int color) {
    for(int i=0; i < n; i++) {
        screen_update_pixel(x+i,y,color);
    }
}

void IO::screen_draw_border(int y,int color) {
    screen_draw_rect(0,y,cols_,color);
}

void IO::screen_refresh() {
    SDL_UpdateTexture(texture_, NULL,frame_,cols_ * sizeof(uint32_t));
    SDL_RenderClear(renderer_)
    SDL_RenderCopy(renderer_,texture_,NULL,NULL);
    SDL_RenderPresent(renderer_);

    process_events();

    vsync();
}

void IO::vsync() {
    using namespace std::chrono;
    auto t = high_resolution_clock::now() - prev_frame_was_at_;
    duration<double> rr(Vic::kRefreshRate);

    auto ttw = duration_cast<milliseconds>(rr - t);
    std::this_thread::sleep_for(ttw);
    prev_frame_was_at_ = std::chrono::high_resolution_clock::now();
}