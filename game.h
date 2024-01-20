#ifndef GAME_UTILS
#define GAME_UTILS 

#include <SDL.h>
#include "shape.h"
#include "ball.h"
#include "bat.h"
        

bool init();
void close();
bool load_media();
void draw();
void update();
void handle_event(SDL_Event *e);



#endif

