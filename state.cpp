#include "state.h"
#include "SDL_events.h"
#include "constants.h"
#include "globals.h"
#include "log.h"
#include <string>


// Global utilities
void set_next_state(GameState *new_state) {

    if ( next_state != ExitState::get()) {
        next_state = new_state;
    }
}

void change_state() {
    if (next_state != NULL) {
        current_state->exit();
        next_state->enter();

        current_state = next_state;
        next_state = NULL;
    }
}

// Intro State

IntroState IntroState::s_intro_state;

IntroState::IntroState() {
}

IntroState* IntroState::get() {
    return &s_intro_state;
}

bool IntroState::enter() {
    bool success = true;

    // Initialize Background
    m_background = Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, {0x00, 0x00, 0x00, 0xFF});

    if (!m_prompt_text.load_from_redered_text("PRESS ENTER TO START", {0xFF, 0xFF, 0xFF, 0xFF})) {
        log_print("Failed to load menu text.");
        success = false;
    }

    m_title_text.TXT_set_font_size(63);
    if (!m_title_text.load_from_redered_text("PONG", {0xFF, 0xFF, 0xFF, 0xFF})) {
        log_print("Failed to load title text.");
        success = false;
    }


    return success;

}

bool IntroState::exit() {
    m_prompt_text.free();
    return true;
}

void IntroState::handle_event(SDL_Event& e) {

    if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN))  {
        set_next_state(PlayState::get());
    }
}

void IntroState::update() {
    return;
}

void IntroState::render() {
    m_background.render();

    m_prompt_text.render( (SCREEN_WIDTH - m_prompt_text.get_width() ) / 2, (SCREEN_HEIGHT - m_prompt_text.get_height()) / 2);
    m_title_text.render( (SCREEN_WIDTH - m_title_text.get_width()) / 2, m_title_text.get_height() + SCREEN_HEIGHT / 10);
}

// Play State

PlayState PlayState::s_play_state;

PlayState::PlayState() {
}

PlayState* PlayState::get() {
    return &s_play_state;
}


bool PlayState::enter() {
    bool success = true;
    m_background = Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, {0x00, 0x00, 0x00, 0xFF});
    m_ball = Ball();
    m_player1_bat = Bat(20, SCREEN_WIDTH / 2 - 50);
    m_player2_bat = Bat(SCREEN_WIDTH - 30, SCREEN_HEIGHT / 2 - 50);
    m_divider = Rectangle(SCREEN_WIDTH / 2 - 5,
            0,
            5,
            SCREEN_WIDTH / 20,
            {0xFF, 0xFF, 0xFF, 0xFF});
    m_player1score_text.TXT_set_font_size(150);
    if (!m_player1score_text.load_from_redered_text("0", {0xFF, 0xFF, 0xFF, 0xFF})) {
        log_print("Failed to load score text 1");
        success = false;

    };
    m_player2score_text.TXT_set_font_size(150);
    if (!m_player2score_text.load_from_redered_text("0", {0xFF, 0xFF, 0xFF, 0xFF})) {
        log_print("Failed to load score text 2");
        success = false;
    };
    return success;
}

bool PlayState::exit() {
    m_player1score_text.free();
    m_player2score_text.free();
    m_ball.reset();
    return true;
}

void PlayState::handle_event(SDL_Event& e) {
    float dt = (SDL_GetTicks() - timer.get_ticks()) / 1000.0f;
    if (e.type == SDL_KEYDOWN) {
        const Uint8* current_key_states = SDL_GetKeyboardState(NULL);
        if (current_key_states[SDL_SCANCODE_W]) {
            m_player1_bat.move_up(dt);
        }
        if (current_key_states[SDL_SCANCODE_S]) {
            m_player1_bat.move_down(dt);
        }
        if (current_key_states[SDL_SCANCODE_UP]) {
            m_player2_bat.move_up(dt);
        }
        if (current_key_states[SDL_SCANCODE_DOWN]) {
            m_player2_bat.move_down(dt);
        }
    }
}

void PlayState::update() {
    m_ball.move(m_player1_bat, m_player2_bat, (SDL_GetTicks() - timer.get_ticks()) / 1000.0f);
    m_player1score_text.TXT_set_font_size(150);
    m_player1score_text.load_from_redered_text(std::to_string(m_player1_bat.get_point()), {0xFF, 0xFF, 0xFF, 0xFF});
    m_player2score_text.TXT_set_font_size(150);
    m_player2score_text.load_from_redered_text(std::to_string(m_player2_bat.get_point()), {0xFF, 0xFF, 0xFF, 0xFF});
    if (m_player1_bat.get_point() > 12 || m_player2_bat.get_point() > 12) {
        set_next_state(WinState::get());
    }
}

void PlayState::render() {
    m_background.render();
    for (int i = 0; i < 19; i++) {
        m_divider.set_position_y((SCREEN_HEIGHT / 20 + 10) * i);
        m_divider.render();
    }
    m_divider.set_position_y(0);
    m_ball.render();
    m_player1score_text.render(SCREEN_WIDTH / 4 - m_player1score_text.get_width() / 2, (SCREEN_HEIGHT - m_player1score_text.get_height()) / 2);
    m_player2score_text.render(SCREEN_WIDTH * 3 / 4 - m_player1score_text.get_width() * 3 / 2, (SCREEN_HEIGHT - m_player2score_text.get_height()) / 2);
    m_player1_bat.render();
    m_player2_bat.render();
}

int PlayState::get_player1_point() {
    return s_play_state.m_player1_bat.get_point();
}

int PlayState::get_player2_point() {
    return s_play_state.m_player2_bat.get_point();
}


// Paused State

WinState WinState::s_win_state;

WinState::WinState() {
}

WinState* WinState::get() {
    return &s_win_state;
}

bool WinState::enter() {
    bool success = false;
    m_background = Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, {0x00, 0x00, 0x00, 0xFF});
    m_winner_text.TXT_set_font_size(150);
    if (PlayState::get_player1_point() > PlayState::get_player2_point()) {
        if (!m_winner_text.load_from_redered_text("P1 WIN", {0xFF, 0xFF, 0xFF, 0xFF})) {
            log_print("Failed to load winner text.");
            success = false;
        }
    }
    else {
        if (!m_winner_text.load_from_redered_text("P2 WIN", {0xFF, 0xFF, 0xFF, 0xFF})) {
            log_print("Failed to load winner text.");
            success = false;
        }
    }

    if (!m_redo_prompt_text.load_from_redered_text("Press Enter to go to main scene", {0xFF, 0xFF, 0xFF, 0xFF})) {
        log_print("Failed to load redo prompt text.");
        success = false;
    }
    if (!m_quit_prompt_text.load_from_redered_text("Press ESC to QUIT", {0xFF, 0xFF, 0xFF, 0xFF})) {
        log_print("Failed to load quit prompt text");
        success = false;
    }
    return success;
}

bool WinState::exit() {
    m_winner_text.free();
    m_redo_prompt_text.free();
    m_quit_prompt_text.free();
    return true;
}

void WinState::handle_event(SDL_Event &e) {
    if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_RETURN)) {
        set_next_state(IntroState::get()); 
    }
    if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
        set_next_state(ExitState::get());
    }
}

void WinState::update() {
    return;
}

void WinState::render() {
    m_background.render();
    m_winner_text.render((SCREEN_WIDTH - m_winner_text.get_width()) / 2, SCREEN_HEIGHT / 3 - m_winner_text.get_height());
    m_redo_prompt_text.render((SCREEN_WIDTH - m_redo_prompt_text.get_width()) / 2, SCREEN_HEIGHT / 2 - m_redo_prompt_text.get_height());
    m_quit_prompt_text.render((SCREEN_WIDTH - m_quit_prompt_text.get_width()) / 2, SCREEN_HEIGHT * 5 / 6 - m_quit_prompt_text.get_height());
}


// Exit State
ExitState ExitState::s_exit_state;

ExitState::ExitState() {

}

ExitState* ExitState::get() {
    return &s_exit_state;
}

bool ExitState::enter() {
    return true;
}

bool ExitState::exit() {
    return true;
}

void ExitState::handle_event(SDL_Event &e) {
    return;
}

void ExitState::update() {
    return;
}

void ExitState::render() {
    return;
}


