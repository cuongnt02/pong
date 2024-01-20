#ifndef STATE_H
#define STATE_H

#include <SDL.h>
#include "texture.h"
#include "shape.h"
#include "bat.h"
#include "ball.h"

class GameState {
public:
    virtual bool enter() = 0;
    virtual bool exit() = 0;
        
    virtual void handle_event( SDL_Event &e ) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    virtual ~GameState(){};

};

void set_next_state(GameState* new_state);
void change_state();

class IntroState : public GameState {

public:
    static IntroState* get();

    bool enter();
    bool exit();

    void handle_event(SDL_Event &e);
    void update();
    void render();
private:
    static IntroState s_intro_state;
    IntroState();
    Rectangle m_background;
    Texture m_prompt_text;
    Texture m_title_text;
};

class PlayState : public GameState {
public:
    static PlayState* get();
    static int get_player1_point();
    static int get_player2_point();
    bool enter();
    bool exit();
    void handle_event(SDL_Event &e);
    void update();
    void render();
private:
    static PlayState s_play_state;
    PlayState();
    Rectangle m_background;
    Rectangle m_divider;
    Bat m_player1_bat;
    Bat m_player2_bat;
    Ball m_ball;
    Texture m_player1score_text;
    Texture m_player2score_text;
};




class WinState : public GameState {
public:
    static WinState* get();
    bool enter();
    bool exit();
    void handle_event(SDL_Event &e);
    void update();
    void render();
private:
    static WinState s_win_state;
    WinState();
    Rectangle m_background;
    Texture m_winner_text;
    Texture m_redo_prompt_text;
    Texture m_quit_prompt_text;
};

class ExitState : public GameState {
public:
    static ExitState* get();
    bool enter();
    bool exit();
    void handle_event(SDL_Event &e);
    void update();
    void render();
private:
    static ExitState s_exit_state;
    ExitState();
};

#endif
