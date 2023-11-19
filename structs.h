#include "share.h"
#include <string>

#ifndef STRUCTS
#define STRUCTS
struct Rect {
    SDL_Rect rect {0, 0, 0, 0};
    SDL_Color color {0x00, 0x00, 0x00, 0x00};
    void render() {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    };
};

struct TextRect {
    std::string text;
    Rect rect;

};
#endif


