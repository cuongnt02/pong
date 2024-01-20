#pragma once

#ifndef SDL_TEXTURE
#define SDL_TEXTURE

#include <string>
#include <SDL.h>

class Texture
{
    public:
        Texture();
        ~Texture();
        bool load_from_file(std::string path);
        bool load_from_redered_text(std::string text, SDL_Color text_color);
        void TXT_set_font_size(int font_size);
        void free();
        void render(int x, int y, SDL_Rect* clip = NULL, double angle=0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int get_width();
        int get_height();

    private:
        static const int DEFAULT_FONT_SIZE = 24;
        int m_width;
        int m_height;
        SDL_Texture* m_texture;
};


#endif
