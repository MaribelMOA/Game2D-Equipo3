#include "sprites.hpp"
#include "../../utilidad/Func_aux.hpp"
#include <iostream>

Sprite::Sprite(std::string file,Coordenadas pos, int w, int h, int sw, int sh)
{
    //no empiezan del centro, empiezan de una equina
    width = w;
    height = h;
    path = file;
    //SDL_Rect a.----b
    //          c   d
    sprite_select={pos.x-(w/2),pos.y-(h/2),width,height};
    sprite_frame={pos.x-(w/2),pos.y-(h/2),width,height};
    sprite_size={sw,sh};
    estado_animacion=nullptr;
   
};


Sprite::~Sprite()
{
    SDL_DestroyTexture(hoja);
    //delete cuando sea del tipo FSMAnimacionIdle
    //delete estado_animacion;
};

bool Sprite::cargar_textura(SDL_Renderer* r)
{
    hoja = IMG_LoadTexture(r,path.c_str());
    if(!hoja)
    {
        std::cout<<SDL_GetError()<<"\n";
        return false;
    }
    
    return true;
};

void Sprite::set_sprite_position(Coordenadas p)
{
    //posicion de la estructura
    //frame es lo que se ve en la pantalla
    //posicion - el tamano
    sprite_frame.x = p.x-(sprite_size.x/2);
    sprite_frame.y = p.y-(sprite_size.y/2);

    
}

Coordenadas Sprite::get_sprite_position()
{
    //regresamos las posicion del frame, 
    return {sprite_frame.x,sprite_frame.y};
};

void Sprite::play_frame(int row, int frame)
{
    //asume que simepre s emovera hacaia la derecha
    //y si tenemos
    sprite_select.x = row+(frame*width);
    sprite_select.y = row*height;//(0,0)->(500,500) etc..
    sprite_select.w = width;
    sprite_select.h = height;
    
};

void Sprite::set_estado_animacion(void *estado)
{
    /*
    estado_animacion->salir(*this);
    delete estado_animacion;
    estado_animacion = estado;
    estado_animacion->entrar(*this);
    */
};