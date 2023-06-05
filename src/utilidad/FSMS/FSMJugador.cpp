#include "FSMJugador.hpp"
#include "../Func_aux.hpp"
#include<SDL.h>
#include<iostream>
#include <sstream>
#include<cmath>

/*
IDLE
*/
EstadoJugadorIDLE::EstadoJugadorIDLE()
{
    strnombre = "IDLE";
    frames_actual_ani=0;
    frames_maxim_ani=6;
};

FSMJugador* EstadoJugadorIDLE::input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse)
{
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});
    if(input.estaPresionado(SDL_SCANCODE_J) & player.get_attack_on()==true)
        return new EstadoJugadorAttack();

    return NULL;
};
void EstadoJugadorIDLE::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=6;
};
void EstadoJugadorIDLE::salir(Jugador& player)
{

};
void EstadoJugadorIDLE::update(Jugador& player,double dt)
{
    player.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>3)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;

};

/*
ATTACK
*/
EstadoJugadorAttack::EstadoJugadorAttack()
{
    strnombre = "ATTACK";
    frames_actual_ani=0;
    frames_maxim_ani=6;
};

FSMJugador* EstadoJugadorAttack::input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse)
{
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});
    if(input.estaPresionado(SDL_SCANCODE_J) &  (player.get_attack_on()==true))
        return new EstadoJugadorAttack();

    return NULL;
};
void EstadoJugadorAttack::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=6;
};
void EstadoJugadorAttack::salir(Jugador& player)
{

};
void EstadoJugadorAttack::update(Jugador& player,double dt)
{
    player.get_sprite()->play_frame(3,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>6)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;

};

/*
MOVER
*/
EstadoJugadorMOVER::EstadoJugadorMOVER(Coordenadas dir)
{
    strnombre = "MOVER";
    direccion = dir;
    velocidad = 15;
    frames_actual_ani=0;
    frames_maxim_ani=6;
};

FSMJugador* EstadoJugadorMOVER::input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse)
{
    //SDL_SCANCODE_UP
    
   
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_J) & (player.get_attack_on()==true))
        return new EstadoJugadorAttack();
    /*
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});

         if(input.estaPresionado(SDL_SCANCODE_DOWN) & input.estaPresionado(SDL_SCANCODE_RIGHT))
        return new EstadoJugadorMOVERIZQ({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_DOWN) & input.estaPresionado(SDL_SCANCODE_LEFT))
        return new EstadoJugadorMOVERDER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_UP) & input.estaPresionado(SDL_SCANCODE_RIGHT))
        return new EstadoJugadorMOVERIZQ({1,1});
    if(input.estaPresionado(SDL_SCANCODE_UP) & input.estaPresionado(SDL_SCANCODE_LEFT))
        return new EstadoJugadorMOVERDER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_J) & player.get_attack_on()==true)
        return new EstadoJugadorAttack();
    */
    //buggy
    
    if(input.nadaPresionado())
        return new EstadoJugadorIDLE();
    

    return NULL;
};
void EstadoJugadorMOVER::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=6;
};
void EstadoJugadorMOVER::salir(Jugador& player){};
void EstadoJugadorMOVER::update(Jugador& player,double dt)
{
    Coordenadas p = player.get_posicion_mundo();
    if (player.en_colision)
    {
     /*   float mag = std::sqrt(player.offsetoverlap.x*player.offsetoverlap.x +player.offsetoverlap.y*player.offsetoverlap.y);
        float rx = player.offsetoverlap.x/mag;
        float ry = player.offsetoverlap.y/mag;

        p.x =(p.x+rx*(-direccion.x)*velocidad) ;
        p.y =(p.y+ry*(-direccion.y)*velocidad) ;*/
    }
    else
    {
        p.x+=(velocidad*direccion.x);
        p.y+=(velocidad*direccion.y);
    }
    player.set_posicion_mundo(p);
    player.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};

/*MOVER IZQ*/
EstadoJugadorMOVERIZQ::EstadoJugadorMOVERIZQ(Coordenadas dir)
{
    strnombre = "MOVER IZQ";
    direccion = dir;
    velocidad = 15;
    frames_actual_ani=0;
    frames_maxim_ani=6;
};

FSMJugador* EstadoJugadorMOVERIZQ::input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse)
{

       if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_J) &  (player.get_attack_on()==true))
        return new EstadoJugadorAttack();

    //buggy
    
    if(input.nadaPresionado())
        return new EstadoJugadorIDLE();
    

    return NULL;
};
void EstadoJugadorMOVERIZQ::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=6;
};
void EstadoJugadorMOVERIZQ::salir(Jugador& player){};
void EstadoJugadorMOVERIZQ::update(Jugador& player,double dt)
{
    Coordenadas p = player.get_posicion_mundo();
    if (player.en_colision)
    {
        /*float mag = std::sqrt(player.offsetoverlap.x*player.offsetoverlap.x +player.offsetoverlap.y*player.offsetoverlap.y);
        float rx = player.offsetoverlap.x/mag;
        float ry = player.offsetoverlap.y/mag;

        p.x =(p.x+rx*(-direccion.x)*velocidad) ;
        p.y =(p.y+ry*(-direccion.y)*velocidad) ;*/
    }
    else
    {
        p.x+=(velocidad*direccion.x);
        p.y+=(velocidad*direccion.y);
    }
    player.set_posicion_mundo(p);
    player.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};


/*MOVER DER*/
EstadoJugadorMOVERDER::EstadoJugadorMOVERDER(Coordenadas dir)
{
    strnombre = "MOVER DER";
    direccion = dir;
    velocidad = 15;
    frames_actual_ani=0;
    frames_maxim_ani=6;
};

FSMJugador* EstadoJugadorMOVERDER::input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse)
{

      if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVERIZQ({1,1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVERDER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_J)  & (player.get_attack_on()==true))
        return new EstadoJugadorAttack();

    //buggy
    
    if(input.nadaPresionado())
        return new EstadoJugadorIDLE();
    

    return NULL;
};
void EstadoJugadorMOVERDER::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=6;
};
void EstadoJugadorMOVERDER::salir(Jugador& player){};
void EstadoJugadorMOVERDER::update(Jugador& player,double dt)
{
    Coordenadas p = player.get_posicion_mundo();
    if (player.en_colision)
    {
        /*float mag = std::sqrt(player.offsetoverlap.x*player.offsetoverlap.x +player.offsetoverlap.y*player.offsetoverlap.y);
        float rx = player.offsetoverlap.x/mag;
        float ry = player.offsetoverlap.y/mag;

        p.x =(p.x+rx*(-direccion.x)*velocidad) ;
        p.y =(p.y+ry*(-direccion.y)*velocidad) ;*/
    }
    else
    {
        p.x+=(velocidad*direccion.x);
        p.y+=(velocidad*direccion.y);
    }
    player.set_posicion_mundo(p);
    player.get_sprite()->play_frame(2,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};