#ifndef SHAPES_H
#define SHAPES_H

#include <SDL.h>
#include "SDL_pixels.h"
#include "interface.h"

class Shape : public IMovable {
    protected:
        int m_x;
        int m_y;
        SDL_Color m_color;
    public:
        virtual ~Shape() {};
        virtual int render() const = 0;
        Shape(int x, int y, SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}) : m_x(x), m_y(y), m_color(color) {};
        virtual void move(int x, int y) override;
        virtual int get_position_x() const;
        virtual int get_position_y() const;
        virtual void set_position_x(int x);
        virtual void set_position_y(int y);
};

class Rectangle : public Shape {
    private:
        int m_width;
        int m_height;
    public:
        Rectangle() : Shape(0, 0) {};
        Rectangle(int x, int y, int w, int h, SDL_Color c) : Shape(x, y, c),  m_width(w), m_height(h) {};
        Rectangle(int x, int y, int w, int h) : Shape(x, y),  m_width(w), m_height(h) {};
        Rectangle(Rectangle& rect) : Shape(rect.m_x, rect.m_y, rect.m_color), m_width(rect.m_width), m_height(rect.m_height) {};
        virtual int render() const override;
        int get_width() const;
        int get_height() const;
};

#endif
