#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include "globals.h"

class Text {
    private:
        int m_x;
        int m_y;
        std::string m_content;
        SDL_Color& m_color;
    public:
        Text(int x, int y, SDL_Color &c, std::string s) : m_x(x), m_y(y), m_color(c), m_content(s) {};
        int render() const;
};

#endif
