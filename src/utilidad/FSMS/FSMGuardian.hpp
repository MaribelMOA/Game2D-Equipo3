#pragma once
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../Estructuras.hpp"
#include<string>

class Guardian; //declaración circular

class FSMGuardian
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
        virtual ~FSMGuardian(){};
        virtual FSMGuardian* input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse)=0;
        virtual void on_entrar(Guardian &g)=0;
        virtual void on_salir(Guardian &g)=0;
        virtual void on_update(Guardian &g,double dt)=0;
        std::string get_namestate()const{return strestado;};
         std::string strestado;
};
class EstadoGuardianIDLE : public FSMGuardian
{
    public:
        EstadoGuardianIDLE();
        virtual ~EstadoGuardianIDLE(){};
        FSMGuardian* input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse);
        void on_entrar(Guardian& g);
        void on_salir(Guardian& g);
        void on_update(Guardian& g,double dt);
         double current_tiempo;
        double idle_tiempo;

    private:
        int contador;
       
       
    
};


//EJEMPLO DE LERP
class EstadoGuardianTransicion : public FSMGuardian
{
    public:
        EstadoGuardianTransicion();
        virtual ~EstadoGuardianTransicion(){};
        FSMGuardian* input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse);
        void on_entrar(Guardian& g);
        void on_salir(Guardian& g);
        void on_update(Guardian& g,double dt);
    private:
        Coordenadas check;
        Coordenadas ant_check;
        Coordenadas centro;
        float distancia;
};

class EstadoGuardianAttack: public FSMGuardian
{
    public:
        EstadoGuardianAttack(Objeto &objlock);
        virtual ~EstadoGuardianAttack(){};
           FSMGuardian* input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse);
        void on_entrar(Guardian& g);
        void on_salir(Guardian& g);
        void on_update(Guardian& g,double dt);
    private:
        Coordenadas centro;
        Objeto *obj;
        bool locked;
     

};