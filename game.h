#pragma once
#ifndef GAME_UTILS
#define GAME_UTILS 

#include "share.h"
#include "timer.h"

class Game {
    public:
        bool init();
        void close();
        bool load_media();
        void draw();
        void update();
        void handle_event(SDL_Event *e);
};


extern Timer timer;

#endif

