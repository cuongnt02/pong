#ifndef BAT
#include "shape.h"

#define BAT
class Bat {
    public:
        Bat();
        Bat(int x, int y, int width = 10, int height = 100, int pts = 0) : m_rect(x, y, width, height), m_point(pts), m_velx(100.0), m_vely(100.0), m_collider({x, y, width, height}) {};
        Bat(Bat &bat);
        void move_up(float dt);
        void move_down(float dt);
        void collide(float offset_x, float offset_y);
        void render();
        void set_position_x(float position);
        void set_position_y(float position);
        float get_position_x() const;
        float get_position_y() const;
        float get_vel_x();
        float get_vel_y();
        int get_point() const;
        void set_point(int point);
        SDL_Rect get_collider() const;
    private:
        int m_point;
        Rectangle m_rect;
        SDL_Rect m_collider;
        float m_velx;
        float m_vely;
};
#endif
