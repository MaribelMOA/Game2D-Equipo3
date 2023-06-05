#pragma once
#include "../../utilidad/Estructuras.hpp"
#include<string>
#include<SDL.h>

class Tile
{
    public:
        Tile(TileInfo info);
        void render(SDL_Renderer *r);
        SDL_Texture* get_textura() const{return atlas;};
        SDL_Rect* get_src() {return &src;};
        SDL_Rect* get_dst() {return &dst;};
        Coordenadas get_sizes()const{return size;};

    private:
        SDL_Rect dst;
        SDL_Rect src;
        Coordenadas pos;
        SDL_Texture *atlas;
        Coordenadas size;
};