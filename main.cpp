#include "game.h"

int main(int argc, char *args[])
{
    Game game = Game();
    if (!game.init())
    {
        printf("Failed to initialize!");
    }
    else
    {
        if (!game.load_media())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Randomize seed
            srand(time(0));

            // Quit flag
            bool quit = false;

            // Event to handle
            SDL_Event e;

            timer.start();
            

            while (!quit)
            {
                // Handles input
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    game.handle_event(&e);
                }

                game.draw();
                if (!end && !paused) {
                    game.update();
                }


            }
            game.close();
        }
    }
    return 0;
}
