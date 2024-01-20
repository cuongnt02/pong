#include "texture.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "share.h"
#include "globals.h"

Texture::Texture()
{
    m_width = 0;
    m_height = 0;
    m_texture = NULL;
}

Texture::~Texture()
{
    free();
}

int Texture::get_height()
{
    return m_height;
}

int Texture::get_width()
{
    return m_width;
}

bool Texture::load_from_file(std::string path)
{
    free();
    SDL_Texture* new_texture = NULL;

    new_texture = IMG_LoadTexture(renderer, path.c_str());
    if (new_texture == NULL)
    {
        printf("Could not create texture %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        // Query size of texture
        SDL_QueryTexture(new_texture, NULL, NULL, &m_width, &m_height);
    }

    m_texture = new_texture;
    return m_texture != NULL;
    

}

void Texture::free()
{
    if (m_texture != NULL)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = { x, y, m_width, m_height};

    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, m_texture, clip, &render_quad, angle, center, flip);
}

bool Texture::load_from_redered_text(std::string text, SDL_Color text_color) {
    
    free();

    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);

    if (text_surface == NULL) {
        printf("Unable to render text surface! SDL_ttf error: %s\n", TTF_GetError());
    }
    else {

        m_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        if (m_texture == NULL) {
            printf("Unable to create texture from surface! SDL error: %s\n", SDL_GetError());
        }
        else {
            m_width = text_surface->w;
            m_height = text_surface->h;
            TTF_SetFontSize(font, DEFAULT_FONT_SIZE);
        }

        SDL_FreeSurface(text_surface);
    }



    return m_texture != NULL;
}

void Texture::TXT_set_font_size(int font_size) {
    TTF_SetFontSize(font, font_size);
}

