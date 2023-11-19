#include "structs.h"

#ifndef BAT
#define BAT
class Bat {
    public:
        Bat();
        void move_up(float y);
        void move_down(float y);
        void collide(float offset_x, float offset_y);
        void render();
        void set_position_x(float position);
        void set_position_y(float position);
        float get_position_x();
        float get_position_y();
        float get_vel_x();
        float get_vel_y();
        SDL_Rect m_collider;
        int* point;
    private:
        float m_velx;
        float m_vely;
        int m_width; 
        int m_height;
        float m_pos_x;
        float m_pos_y;
        Rect m_rect;
};
#endif
