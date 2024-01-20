#ifndef BALL_H
#define BALL_H

#include "bat.h"
#include "shape.h"

class Ball {
    public:
        Ball();
        Ball(int x, int y, int width = 10, int height = 10) : m_rect(x, y, width, height) {};
        void move(Bat &bat_left, Bat &bat_right, float dt);
        void collide(float offset_x, float offset_y) const;
        void render();
        float get_position_x() const;
        float get_position_y() const;
        void reset();
    private:
        void set_position(float x, float y);
        Rectangle m_rect;
        float x;
        float y;
        float m_velx;
        float m_vely;
        float m_speed;
        SDL_Rect m_collider;
};

#endif 
