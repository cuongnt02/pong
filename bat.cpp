#include "bat.h"

Bat::Bat() {
    m_width = 10;
    m_height = 100;
    m_rect = {
        {0, 0, m_width, m_height},
        {0xFF, 0xFF, 0xFF, 0xFF}
    };
    m_velx = 100;
    m_vely = 200;
    m_pos_x = 0;
    m_pos_y = 0;
    m_collider.w = m_width + 10;
    m_collider.h = m_height + 10;
}

void Bat::move_up(float y) {
    m_pos_y -= y;
    if (m_pos_y < 0) {
        m_pos_y += y;
    }
    m_collider.y = m_pos_y;
    set_position_y(m_pos_y);
}

void Bat::move_down(float y) {
    m_pos_y += y;
    if (m_pos_y + m_height > SCREEN_HEIGHT) {
        m_pos_y -= y;
    }
    m_collider.y = m_pos_y;
    set_position_y(m_pos_y);
}


void Bat::render(){
    m_rect.render();
}

void Bat::set_position_x(float position) {
    m_pos_x = position;
    m_rect.rect.x = m_pos_x;
    m_collider.x = m_rect.rect.x;
}

void  Bat::set_position_y(float position) {
    m_pos_y = position;
    m_rect.rect.y = m_pos_y;
    m_collider.y = m_rect.rect.y;
}

float Bat::get_vel_x() {
    return m_velx;
}

float Bat::get_vel_y() {
    return m_vely;
}
