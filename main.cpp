#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "game.h"
#include "log.h"
#include "globals.h"
#include "state.h"
#include <ctime>


SDL_Event e;

static void main_loop(void* args) {
    if (current_state == ExitState::get()) {
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
        return;
    }

    while (SDL_PollEvent(&e))
    {
        current_state->handle_event(e);
        if (e.type == SDL_QUIT) {
            set_next_state(ExitState::get());
        }

    }
    current_state->update();
    change_state();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    current_state->render();

    SDL_RenderPresent(renderer);
}


int main(int argc, char *args[])
{
    log_init("log.txt");
    if (!init())
    {
        log_print("Failed to initialize!\n");
    }
    else
    {
        if (!load_media())
        {
            log_print("Failed to load media!\n");
        }
        else
        {
            // Randomize seed
            srand(time(0));

            timer.start();
            #ifdef __EMSCRIPTEN__
            emscripten_set_main_loop_arg(main_loop, NULL, 0, 1);
            #else
            current_state = IntroState::get();
            current_state->enter();
            while (current_state != ExitState::get())
            {
                main_loop(NULL);   
            }
            #endif
        }
    }
    log_close();
    close();
    return EXIT_SUCCESS;
}
