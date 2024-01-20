#include "bat.h"
#include "constants.h"
#include "log.h"
#include <string>

Bat::Bat() {
    m_velx = 100;
    m_vely = 200;
    m_collider.w = m_rect.get_width() + 10;
    m_collider.h = m_rect.get_height() + 10;
}

void Bat::move_up(float dt) {
    float pos_y = get_position_y();
    pos_y -= dt*m_velx;
    if (pos_y < 0) {
        pos_y += dt*m_velx;
    }
    m_collider.y = pos_y;
    set_position_y(pos_y);
}

void Bat::move_down(float dt) {
    float pos_y = get_position_y();
    pos_y += dt*m_velx;
    if (pos_y + m_rect.get_height() > SCREEN_HEIGHT) {
        pos_y -= dt*m_velx;
    }
    m_collider.y = pos_y;
    set_position_y(pos_y);
    log_print(std::to_string(get_position_y()));
}


void Bat::render(){
    m_rect.render();
}

void Bat::set_position_x(float position) {
    log_print(std::to_string(position));
    m_rect.set_position_x(position);
    log_print(std::to_string(get_position_x()));
    m_collider.x = m_rect.get_position_x();
}

void  Bat::set_position_y(float position) {
    m_rect.set_position_y(position);
    m_collider.y = m_rect.get_position_y();
}

float Bat::get_vel_x() {
    return m_velx;
}

float Bat::get_vel_y() {
    return m_vely;
}

int Bat::get_point() const {
    return m_point;
}

void Bat::set_point(int point) {
    m_point = point;
}
SDL_Rect Bat::get_collider() const {
    return m_collider;
}

float Bat::get_position_x() const {
    return m_rect.get_position_x();
}

float Bat::get_position_y() const {
    return m_rect.get_position_y();
}
