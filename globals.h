#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>

#include "texture.h"
#include "timer.h"
#include <SDL_ttf.h>
#include "state.h"

// Window that we render to
extern SDL_Window* window;

// The renderer
extern SDL_Renderer* renderer;

// The font
extern TTF_Font* font;


// Screen Textures
extern Texture font_texture;


// The timer
extern Timer timer;


// Logger
extern std::ofstream outfile;

extern GameState* current_state;
extern GameState* next_state;



#endif
