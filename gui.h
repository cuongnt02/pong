/**
 * GUI CLASS - EXPERIMENTAL - NOT USED
 * 
 * **/
#ifndef GUI_H
#define GUI_H

#include "interface.h"
#include "text.h"
#include "shape.h"
#include <SDL.h>

class GUI : public IMovable {
    protected:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
    public:
        GUI(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height){};
        virtual void render() const;
        virtual void move(int x, int y) override {
            m_x = x;
            m_y = y;
        }
        virtual void handle_event(SDL_Event &e);
};

class Button : public GUI {
    private:
        Text m_text;
        Rectangle m_outer_rect;
    public:
        Button(int x, int y, int width, int height, Text& text, Rectangle& outer_rect) : GUI(x, y, width, height), m_text(text), m_outer_rect(outer_rect) {};
        void render() const override;
        void handle_event(SDL_Event &e) override;
};

#endif
