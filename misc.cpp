#include "misc.h"


bool check_collision(SDL_Rect rect_a, SDL_Rect rect_b) {
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    left_a = rect_a.x;
    right_a = rect_a.x + rect_a.w;
    top_a = rect_a.y;
    bottom_a = rect_a.y + rect_a.h;

    left_b = rect_b.x;
    right_b = rect_b.x + rect_b.w;
    top_b = rect_b.y;
    bottom_b = rect_b.y + rect_b.h;

    if (bottom_a <= top_b) return false;
    if (top_a >= bottom_b) return false;
    if (left_a >= right_b) return false;
    if (right_a <= left_b) return false;

 //   if (collide)
//        printf("collide: %d", collide);

    return true;
}
