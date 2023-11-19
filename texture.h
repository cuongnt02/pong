#pragma once

#ifndef SDL_TEXTURE
#define SDL_TEXTURE

#include "common.h"

class Texture
{
    public:
        Texture();
        ~Texture();
        bool load_from_file(std::string path);
        bool load_from_redered_text(std::string text, SDL_Color text_color);
        void free();
        void render(int x, int y, SDL_Rect* clip = NULL, double angle=0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int get_width();
        int get_height();

    private:
        int m_width;
        int m_height;
        SDL_Texture* m_texture;
};


#endif
