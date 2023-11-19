#include "game.h"
#include "SDL_keyboard.h"
#include "SDL_scancode.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include "ball.h"
#include "bat.h"
#include <string>

// Global properties
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

// Graphics properties
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Global font
TTF_Font* font = NULL;

// Graphic defined textures
Texture card_texture;
Texture font_texture;


// Time tracker 
Timer timer;

// Black Background
Rect background;

// Middle vertical line
Rect middle_line;

// ball texture
Ball ball = Ball();
// bat textures
Bat bat_left = Bat();
Bat bat_right = Bat();

// Game Logic 
int P1_score = 0;
int P2_score = 0;
bool end = false;
bool paused = false;




bool Game::init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize SDL! SDL_Error: %s", SDL_GetError());
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
            printf("Could not initialize window! SDL_Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            {
                printf("WARNING: Linear texture filtering not enabled!");
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Could not create renderer! SDL_Error: %s", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int img_flag = IMG_INIT_PNG;
                if (!(IMG_Init(img_flag) & img_flag))
                {
                    printf("Could not initialize SDL_image! SDL_image Error: %s", IMG_GetError());
                    success = false;
                }

                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    timer = Timer();
    return success;
}

void Game::close()
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

void init_bat() {
    bat_left.set_position_x(0);
    bat_left.set_position_y(0);
    bat_right.set_position_x(SCREEN_WIDTH - 10);
    bat_right.set_position_y(0);
    bat_left.point = &P1_score;
    bat_right.point = &P2_score;
}

void init_middle_rect() {
    middle_line.rect = {SCREEN_WIDTH / 2 - 5, 0, 10, SCREEN_HEIGHT / 20};
    middle_line.color = {0xFF, 0xFF, 0xFF, 0xFF};
}


void set_font_size(int font_size) {
    if (TTF_SetFontSize(font, font_size) < 0) {
        printf("Set Font Size Failed: SDL_TTF Error: %s\n", TTF_GetError());    
    }
}

// Load static assets
bool Game::load_media()
{
    bool success = true;

    font = TTF_OpenFont("../assets/fonts/Play-Regular.ttf", 24);
    if (font == NULL) {
        printf("Failed to load font: Lostina! SDL_ttf error: %s\n", TTF_GetError());
        success = false;
    }

    background.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    background.color = {0x00, 0x00, 0x00, 0xFF};
    init_middle_rect();
    init_bat();

    return success;
}


void draw_background() {
    background.render();
}

void draw_middle_line() {
    for (int i = 0; i < 19; i++) {
        Rect rect = {};
        rect.rect = { 
            SCREEN_WIDTH / 2 - 5,
            (SCREEN_HEIGHT / 20 + 10) * i,
            10, SCREEN_HEIGHT / 20
        };
        rect.color = {0xFF, 0xFF, 0xFF, 0xFF};
        rect.render();
    }
}

void draw_ball() {
    ball.render();
}

void draw_bat() {
    bat_left.render();    
    bat_right.render();
}

void draw_text() {
    set_font_size(200);
    font_texture.load_from_redered_text(std::to_string(P1_score), {0xFF, 0xFF, 0xFF, 0xFF});
    font_texture.render(SCREEN_WIDTH / 4 - 100, SCREEN_HEIGHT / 2 - 100);
    font_texture.load_from_redered_text(std::to_string(P2_score), {0xFF, 0xFF, 0xFF, 0xFF});
    font_texture.render(SCREEN_WIDTH * 3 / 4 - 100, SCREEN_HEIGHT / 2 - 100);
}

void draw_overlay() {
    Rect overlay = {};
    overlay.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    overlay.color = {0x00, 0x00, 0x00, 0xFF};
    overlay.render();

    set_font_size(50);
    font_texture.load_from_redered_text("Press P to continue", {0xFF, 0xFF, 0xFF, 0xFF});
    font_texture.render(SCREEN_WIDTH / 2 - 225, SCREEN_HEIGHT / 2 - 25);
}

void draw_end_screen() {
    Rect overlay = {};
    overlay.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    overlay.color = {0x00, 0x00, 0x00, 0xFF};
    overlay.render();

    std::string end_text;
    if (P1_score > 12) {
        end_text = "P1 WIN";
    }
    else if (P2_score > 12) {
        end_text = "P2 WIN";
    }
    else {
        end_text = "AN ERROR OCCURRED";
    }

    set_font_size(50);
    font_texture.load_from_redered_text(end_text, {0xFF, 0xFF, 0xFF, 0xFF});
    font_texture.render(SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 25);
}


void Game::draw() {
    SDL_RenderClear(renderer);

    draw_background();
    draw_middle_line();
    draw_ball();
    draw_bat();
    draw_text();
    if (paused) {
        draw_overlay();
    }
    if (end) {
        draw_end_screen();
    }

    SDL_RenderPresent(renderer);
}

void reset() {
    P1_score = 0;
    P2_score = 0;
    end = false;
    ball.reset();
}

void Game::update() {
    float dt = (SDL_GetTicks() - timer.get_ticks()) / 1000.0f;
    ball.move(bat_left, bat_right, dt);
    if (P1_score > 12 || P2_score > 12) {
        end = true;
    }
}

void Game::handle_event(SDL_Event *e) {

    float dt = (SDL_GetTicks() - timer.get_ticks()) / 1000.0f;
    if (e->type == SDL_KEYDOWN) {
        const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
        if (current_key_states[SDL_SCANCODE_W]) {
            bat_left.move_up(dt*bat_left.get_vel_y());
        }
        if (current_key_states[SDL_SCANCODE_S]) {
            bat_left.move_down(dt*bat_left.get_vel_y());
        }
        if (current_key_states[SDL_SCANCODE_UP]) {
            bat_right.move_up(dt*bat_right.get_vel_y());
        }
        if (current_key_states[SDL_SCANCODE_DOWN]) {
            bat_right.move_down(dt*bat_right.get_vel_y());
        }
        if (current_key_states[SDL_SCANCODE_P]) {
            paused = !paused;
        }
        if (current_key_states[SDL_SCANCODE_RETURN] && end) {
            reset();
        }

    }
}


