#include "ball.h"
#include <random>
#include "misc.h"
#include "constants.h"
#include <cmath>
#include <string>
#include "log.h"

Ball::Ball() {
    int width = 10;
    int height = 10;
    x = (SCREEN_WIDTH - width) / 2.0f;
    y = (SCREEN_HEIGHT - height) / 2.0f;
    m_rect = Rectangle((int) x, (int) y, width, height);
    m_collider.w = 10;
    m_collider.h = 10;
    m_collider.x = x;
    m_collider.y = y;
    m_velx = (rand() - RAND_MAX / 2 >= 0 ? 1 : -1) * 20;
    m_vely = (rand() - RAND_MAX / 2 >= 0 ? 1 : -1) * 20;
}

void Ball::render() {
    m_rect.render();
}


float Ball::get_position_x() const {
    return m_rect.get_position_x();
}

float Ball::get_position_y() const {
    return m_rect.get_position_y();
}

void Ball::set_position(float x, float y) {
    m_rect.move(round(x), round(y));
}

void Ball::move(Bat& bat_left, Bat& bat_right, float dt) {
    float velx = (dt * m_velx);
    float vely = (dt * m_vely);

    float pos_x = get_position_x() + velx + m_rect.get_width();
    float pos_y = get_position_y() + vely + m_rect.get_width();

    x += velx;
    m_collider.x = x;
    // if (pos_x > SCREEN_WIDTH || pos_x < 0) {
    //     x -= m_velx;
    //     m_velx *= (-1);
    // }
    if (pos_x > SCREEN_WIDTH) {
        bat_left.set_point(bat_left.get_point() + 1);
        reset();
    }

    if (pos_x < 0) {
        bat_right.set_point(bat_right.get_point() + 1);
        reset();
    }

    y += vely;
    m_collider.y = y;
    if ( pos_y > SCREEN_HEIGHT || pos_y < 0) {
        y -= vely;
        m_vely *= (-1);
    }


    if (check_collision(m_collider, bat_left.get_collider())) {
        x -= velx;
        m_velx *= (-1);
//        x += m_velx;
    }
    if (check_collision(m_collider, bat_right.get_collider())) {
        x -= velx;
        m_velx *= (-1);
//        x += m_velx;
    }

    set_position(x, y);
}

void Ball::reset() {
    x = (SCREEN_WIDTH - m_rect.get_width()) / 2.0f;
    y = (SCREEN_HEIGHT - m_rect.get_width()) / 2.0f;
    m_velx = (rand() - RAND_MAX / 2 >= 0 ? 1 : -1) * 20;
    m_vely = (rand() - RAND_MAX / 2 >= 0 ? 1 : -1) * 20;
    
}
