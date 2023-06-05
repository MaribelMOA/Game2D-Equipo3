#pragma once
#include<SDL.h>
#include<vector>
#include "../utilidad/Estructuras.hpp"
#include "../objetos/Figuras.hpp"
#include "imagen/sprites.hpp"
#include "imagen/tiles.hpp"

class Pipeline
{
    public:
        Pipeline(SDL_Renderer &ren);

        //quitar copias
        Pipeline(const Pipeline&) = delete;
        Pipeline &operator=(const Pipeline&) = delete;

        void puntos(std::vector<Coordenadas> p,SDL_Color c);
        void lineas(std::vector<Coordenadas> p,SDL_Color c);
        void figuras(std::vector<Figura*> f);
        void figuras(Figura* f);
        void pintar_texturas(Sprite* obj);
        void pintar_texturas(Tile* obj);
        bool cargar_texturas(Sprite* obj);

    private:
        SDL_Renderer *ptrren;
        
};