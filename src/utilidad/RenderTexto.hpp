#pragma once
#include <SDL.h>
#include<string>
#include <SDL_ttf.h>

class RenderTexto
{
    public:
        ~RenderTexto();
        static RenderTexto& get();
        static void render_texto(SDL_Renderer *ren, int x, int y, std::string texto, int fontsize, SDL_Color color, std::string font="SunnySpells");
        static void render_texto(SDL_Renderer *ren, int x, int y, std::string texto, int w, int h,SDL_Color color);
    
    private:
        RenderTexto();
        static RenderTexto* instancia;

        SDL_Rect font_rect;
        SDL_Texture *font_texture;
        SDL_Surface *font_surface;
        
        //fonts para este caso solo uno
        TTF_Font* font_default;

        static bool inicio; 
};