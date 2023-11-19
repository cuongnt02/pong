#include "ball.h"
#include <random>
#include "misc.h"

Ball::Ball() {
    m_size = 10;
    m_rect = {
        {(SCREEN_WIDTH - m_size) / 2, (SCREEN_HEIGHT - m_size) / 2, m_size, m_size},
        {0xFF, 0xFF, 0xFF, 0xFF}
    };
    m_speed = 10.0f;
    m_pos_x = m_rect.rect.x;
    m_pos_y = m_rect.rect.y;
    m_collider.w = 20;
    m_collider.h = 20;
    m_velx = (rand() - RAND_MAX / 2 >= 0 ? 1 : -1);
    m_vely = (rand() - RAND_MAX / 2 >= 0 ? 1 : -1);
}

void Ball::render() {
    m_rect.render();
}


float Ball::get_position_x() {
    return m_rect.rect.x;
}

float Ball::get_position_y() {
    return m_rect.rect.y;
}

void Ball::set_position(float x, float y) {
    m_rect.rect.x = (int)x;
    m_rect.rect.y = (int)y;
}

void Ball::move(Bat bat_left, Bat bat_right, float dt) {
    m_velx = dt * m_speed * (m_velx < 0 ? -1 : 1) / 2.0f;
    m_vely = dt * m_speed * (m_vely < 0 ? -1 : 1) / 2.0f;

    float pos_x = m_pos_x + m_velx + m_size / 2.0f;
    float pos_y = m_pos_y + m_vely + m_size / 2.0f;

    m_pos_x += m_velx;
    m_collider.x = m_pos_x;
    // if (pos_x > SCREEN_WIDTH || pos_x < 0) {
    //     m_pos_x -= m_velx;
    //     m_velx *= (-1);
    // }
    if (pos_x > SCREEN_WIDTH) {
        m_pos_x -= m_velx;
        m_velx *= (-1);
        *(bat_left.point) = *(bat_left.point) + 1;
        reset();
        return;
    }

    if (pos_x < 0) {
        m_pos_x -= m_velx;
        m_velx *= (-1);
        *(bat_right.point) = *(bat_right.point) + 1;
        reset();
        return;
    }

    m_pos_y += m_vely;
    m_collider.y = m_pos_y;
    if ( pos_y > SCREEN_HEIGHT || pos_y < 0) {
        m_pos_y -= m_vely;
        m_vely *= (-1);
    }

    if (check_collision(m_collider, bat_left.m_collider)) {
        m_pos_x -= m_velx;
        m_velx *= (-1);
        m_pos_x += m_velx;
        *(bat_left.point) = *(bat_left.point) + 1;
    }
    if (check_collision(m_collider, bat_right.m_collider)) {
        m_pos_x -= m_velx;
        m_velx *= (-1);
        m_pos_x += m_velx;
        *(bat_right.point) = *(bat_right.point) + 1;
    }

    set_position(m_pos_x, m_pos_y);
}

void Ball::reset() {
    m_pos_x = (SCREEN_WIDTH - m_size) / 2.0f;
    m_pos_y = (SCREEN_HEIGHT - m_size) / 2.0f;
}
