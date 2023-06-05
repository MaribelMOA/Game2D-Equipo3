#include "Objeto.hpp"
#include "../motor/Pipeline.hpp"
#include <iostream>
#include "../utilidad/Func_aux.hpp"

void Objeto::render(SDL_Renderer* r)
{

    Pipeline temp(*r);
    if(!sprite && !tile)
    {    
        temp.figuras(avatar);
    }  
    else if(!sprite && tile)
    {
        temp.pintar_texturas(tile);
    }
    else 
    {
        temp.pintar_texturas(sprite);
    }

    if(render_colbox)
        temp.figuras(col_box);
};

void Objeto::set_posicion_camara(Coordenadas p)
{
    posicion_camara = p;
};

void Objeto::set_posicion_mundo(Coordenadas p)
{
    posicion_mundo =p;
    if(avatar)
    {
        avatar->set_position(p.x,p.y);
        avatar->update_vertices();
    }
    
    col_box->set_position(p.x,p.y);
    col_box->update_vertices();
    
    if(sprite)
        sprite->set_sprite_position(p);
    if(tile)
    {    
        tile->get_dst()->x=p.x-tile->get_sizes().x/2;
        tile->get_dst()->y=p.y-tile->get_sizes().y/2;
    }

    
};
void Objeto::set_posx(int x)
{
    posicion_mundo.x=x;
    if(avatar)
    {
        avatar->set_position(posicion_mundo.x,posicion_mundo.y);
        avatar->update_vertices();
    }
    
    col_box->set_position(posicion_mundo.x,posicion_mundo.y);
    col_box->update_vertices();
    if(sprite)
        sprite->set_sprite_position(posicion_mundo);
};
void Objeto::set_posy(int y)
{
    posicion_mundo.y=y;
    if(avatar)
    {
        avatar->set_position(posicion_mundo.x,posicion_mundo.y);
        avatar->update_vertices();
    }
    
    col_box->set_position(posicion_mundo.x,posicion_mundo.y);
    col_box->update_vertices();
    if(sprite)
        sprite->set_sprite_position(posicion_mundo);
};