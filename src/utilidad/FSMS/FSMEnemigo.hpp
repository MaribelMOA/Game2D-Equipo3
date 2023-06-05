#pragma once
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../Estructuras.hpp"
#include "../Tiempo.hpp"
#include<string>

class Enemigo; //declaración circular

class FSMEnemigo
{
    protected:
        float vel;
        Coordenadas pos_final;
        Coordenadas pos_inicial;
        int frames_actual;
        int frames_maximo;
        int frame_dt{0};
         int frames_actual_ani;
        int frames_maxim_ani;
         int delay;
        double init_tiempo;
        int past_tiempo;
        bool check;
        
    
    public:
        virtual ~FSMEnemigo(){};
        virtual FSMEnemigo* input_handle(Enemigo &en, KeyOyente &keys, MouseOyente& mouse)=0;
        virtual void on_entrar(Enemigo &en)=0;
        virtual void on_salir(Enemigo &en)=0;
        virtual void on_update(Enemigo &en,double dt)=0;
        std::string get_namestate()const{return strestado;};
         std::string strestado;
};
class EstadoEnemigoMover : public FSMEnemigo
{
    public:
        EstadoEnemigoMover(Coordenadas dir);
        virtual ~EstadoEnemigoMover(){};
        FSMEnemigo* input_handle(Enemigo &en, KeyOyente &keys, MouseOyente& mouse);
        void on_entrar(Enemigo& en);
        void on_salir(Enemigo& en);
        void on_update(Enemigo& en,double dt);
           int contador;
        double current_tiempo;
        double idle_tiempo;
    private:
        Coordenadas direccion;

};



//EJEMPLO DE LERP
class EstadoEnemigoTransicion : public FSMEnemigo
{
    public:
        EstadoEnemigoTransicion();
        virtual ~EstadoEnemigoTransicion(){};
        FSMEnemigo* input_handle(Enemigo &en, KeyOyente &keys, MouseOyente& mouse);
        void on_entrar(Enemigo &en);
        void on_salir(Enemigo &en);
        void on_update(Enemigo &en,double dt);
       // Coordenadas normalizar_vector(const Coordenadas& vector);
    private:
        Coordenadas check;
        Coordenadas ant_check;
        Coordenadas centro;
        float distancia;
};

class EstadoEnemigoAttack: public FSMEnemigo
{
    public:
        EstadoEnemigoAttack(Objeto &objlock);
        virtual ~EstadoEnemigoAttack(){};
        FSMEnemigo* input_handle(Enemigo &en, KeyOyente &keys, MouseOyente& mouse);
        void on_entrar(Enemigo &en);
        void on_salir(Enemigo &en);
        void on_update(Enemigo &en,double dt);
    private:
        Coordenadas centro;
        Objeto *obj;
        bool locked;
           

};