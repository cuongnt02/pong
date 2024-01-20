#include "globals.h"
#include <fstream>


// The window we render to
SDL_Window* window = NULL;


// The renderer
SDL_Renderer* renderer = NULL;

// The Timer
Timer timer = Timer();

// The Texture
TTF_Font *font = NULL;

// The Font Texture
Texture font_texture = Texture();

// Log output
std::ofstream outfile;

// Game state
GameState* current_state = NULL;
GameState* next_state = NULL;



