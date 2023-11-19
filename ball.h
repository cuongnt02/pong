#include "structs.h"
#include "bat.h"
class Ball {
    public:
        Ball();
        void move(Bat bat_left, Bat bat_right, float dt);
        void collide(float offset_x, float offset_y);
        void render();
        void set_position(float x, float y);
        float get_position_x();
        float get_position_y();
        void reset();
    private:
        Rect m_rect;
        float m_velx;
        float m_vely;
        float m_speed;
        int m_size; 
        float m_pos_x;
        float m_pos_y;
        SDL_Rect m_collider;
};

