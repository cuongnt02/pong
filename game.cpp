#include "game.h"
#include "globals.h"
#include "constants.h"
#include "log.h"
#include <string>
#include <SDL_image.h>



bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        log_print("Could not initialize SDL! SDL_Error: %s\n" + std::string(SDL_GetError()));
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Pong",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            log_print("Could not initialize window! SDL_Error: %s\n" + std::string(SDL_GetError()));
            success = false;
        }
        else
        {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            {
                log_print("WARNING: Linear texture filtering not enabled!\n");
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if (renderer == NULL)
            {
                log_print("Could not create renderer! SDL_Error: %s\n" + std::string(SDL_GetError()));
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int img_flag = IMG_INIT_PNG;
                if (!(IMG_Init(img_flag) & img_flag))
                {
                    log_print("Could not initialize SDL_image! SDL_image Error: %s\n" + std::string(IMG_GetError()));
                    success = false;
                }

                if (TTF_Init() == -1) {
                    log_print("SDL_ttf could not initialize! SDL_ttf error: %s\n" + std::string(TTF_GetError()));
                    success = false;
                }
            }
        }
    }
    timer = Timer();
    return success;
}

void close()
{
    // Destroy graphics
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    TTF_CloseFont(font);
    font = NULL;

    // Quits SDL
    SDL_Quit();
    IMG_Quit();
}



// Load static assets
bool load_media()
{
    bool success = true;

    font = TTF_OpenFont("../assets/fonts/Play-Regular.ttf", 24);
    if (font == NULL) {
        log_print("Failed to load font: Lostina! SDL_ttf error: %s\n" + std::string(TTF_GetError()));
        success = false;
    }
    return success;
}
