#pragma once
#include "../../utilidad/Estructuras.hpp"
#include<SDL.h>
#include<SDL_image.h>
#include<string>

class Sprite 
{
    public:
        Sprite(std::string file, Coordenadas pos, int w, int h,int sw, int sh);
        //posicion del mundo, tamano del sprite, y tamano de la hoja?
        ~Sprite();

        SDL_Texture* get_textura() const{return hoja;};
        SDL_Rect *get_sprite_src(){return &sprite_select;}
        SDL_Rect *get_sprite_frame(){return &sprite_frame;};
        bool cargar_textura(SDL_Renderer* r);
        void set_sprite_position(Coordenadas p);
        Coordenadas get_sprite_position();
        Coordenadas get_sprite_sizes()const{return sprite_size;};

        void play_frame(int row, int frame);
        void set_estado_animacion(void* estado);

    private:
        SDL_Rect sprite_select;//cuadro que se mueve
        SDL_Rect sprite_frame;//lo que pinta
        SDL_Texture *hoja;
        int width;
        int height;
        std::string path;
        void *estado_animacion;
        int max_frames;
        Coordenadas sprite_size;
        
};