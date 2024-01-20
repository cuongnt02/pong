#include "shape.h"
#include "globals.h"
#include "log.h"


// Shape
int Shape::get_position_x() const {
    return m_x;
}

int Shape::get_position_y() const {
    return m_y;
}

void Shape::move(int x, int y) {
    m_x = x;
    m_y = y;
}
void Shape::set_position_x(int x){
    m_x = x;
}
void Shape::set_position_y(int y){
    m_y = y;
}

// Rectangle
int Rectangle::render() const {
    SDL_Rect rect = {m_x, m_y, m_width, m_height};
    int result = SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    if (result < 0) {
        log_print(SDL_GetError());
        return 0;
    }

    result = SDL_RenderFillRect(renderer, &rect);
    if (result < 0) {
        log_print(SDL_GetError());
        return 0;
    }
    return 1;
}

int Rectangle::get_width() const {
    return m_width;
}

int Rectangle::get_height() const {
    return m_height;
}
