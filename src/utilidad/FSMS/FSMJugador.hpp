#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include<string>

class Jugador; //forward declaration
class FSMJugador
{
    protected:
        std::string strnombre;
    
    public:
        virtual ~FSMJugador(){};
        virtual FSMJugador* input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse)=0;
        virtual void entrar(Jugador& player)=0;
        virtual void salir(Jugador& player)=0;
        virtual void update(Jugador& player,double dt)=0;
        std::string get_namestate()const{return strnombre;};
};

class EstadoJugadorIDLE : public FSMJugador
{
    public:
        EstadoJugadorIDLE();
        virtual ~EstadoJugadorIDLE(){};
        FSMJugador* input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);

    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
    
};

class EstadoJugadorMOVER : public FSMJugador
{
    public:
        EstadoJugadorMOVER(Coordenadas dir);
        virtual ~EstadoJugadorMOVER(){};
        FSMJugador* input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};
class EstadoJugadorMOVERIZQ : public FSMJugador
{
    public:
        EstadoJugadorMOVERIZQ(Coordenadas dir);
        virtual ~EstadoJugadorMOVERIZQ(){};
        FSMJugador* input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};
class EstadoJugadorMOVERDER : public FSMJugador
{
    public:
        EstadoJugadorMOVERDER(Coordenadas dir);
        virtual ~EstadoJugadorMOVERDER(){};
        FSMJugador* input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};

class EstadoJugadorAttack : public FSMJugador
{
    public:
        EstadoJugadorAttack();
        virtual ~EstadoJugadorAttack(){};
        FSMJugador* input_handle(Jugador& player,KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);

    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};