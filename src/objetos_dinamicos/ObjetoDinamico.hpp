#pragma once
#include "../objetos/Objeto.hpp"
#include "../objetos_estaticos/ObjetoEstatico.hpp"
#include "../motor/KeyOyente.hpp"
#include "../motor/MouseOyente.hpp"
#include "../utilidad/FSMS/FSMJugador.hpp"
#include "../utilidad/FSMS/FSMEnemigo.hpp"
#include "../utilidad/FSMS/FSMGuardian.hpp"
#include<SDL.h>
#include<string>
class FSMJugador;//forward declaration
class FSMEnemigo;//forward declaration
class FSMGuardian;//forward declaration

class ObjetoDinamico : public Objeto
{
    public:
        virtual ~ObjetoDinamico(){};
        virtual void update(double dt)=0;
        float get_dtgf()const{return dtgravedad;};
        void set_dtgf(float v){dtgravedad=v;};

        //forma general de convertir cualquier puntero si se conoce la clase
        virtual void set_estado(void* estado)=0;
        virtual void* get_estado()=0;

        Coordenadas offsetoverlap;
    protected:
        float dtgravedad{0};
        
};


class Jugador : public ObjetoDinamico
{
    public:
        virtual ~Jugador(){};
        Jugador(float vida, int x, int y,SDL_Color c );
        Jugador(std::string path_sprite,float vida,int atk, int x, int y, int w, int h,int sw,int sh, SDL_Color c );
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};

        void set_estado(void* estado);
        void* get_estado();

        void set_size(Coordenadas size){this->size = size;};
        Coordenadas get_size(){return size;};

        void set_gemas(int gemas){this->gemas = gemas;};
        int get_gemas(){return gemas;};

        void set_plantas(int plantas){this->plantas = plantas;};
        int get_plantas(){return plantas;};

        void set_colisionables(std::vector<Plataformas*> colisionables){this->colisionables = colisionables;};
        std::vector<Plataformas*> get_colisionables(){return colisionables;};

        void set_ataque(int ataque){this->ataque = ataque;};
        int get_ataque(){return ataque;};

        void set_colision_gemas(bool colision_gemas){this->colision_gemas = colision_gemas;};
        bool get_colision_gemas(){return colision_gemas;};

        void set_colision_plantas(bool colision_plantas){this->colision_plantas = colision_plantas;};
        bool get_colision_plantas(){return colision_plantas;};

        void set_colision_guardian(bool colision_guardian){this->colision_guardian = colision_guardian;};
        bool get_colision_guardian(){return colision_guardian;};

        void set_colision_artefacto(bool colision_artefacto){this->colision_artefacto = colision_artefacto;};
        bool get_colision_artefacto(){return colision_artefacto;};

        void set_colision_enemigo(bool colision_enemigo){this->colision_enemigo = colision_enemigo;};
        bool get_colision_enemigo(){return colision_enemigo;};

        void set_attack_on(bool attack_on){this->attack_on = attack_on;};
        bool get_attack_on(){return attack_on;};

        void checar_colisiones();
    private:
        FSMJugador* estado_actual;
        Coordenadas piso;
        std::vector<Plataformas*> colisionables;
        Coordenadas size;
        bool colision_gemas;
        bool colision_plantas;
        bool colision_guardian;
        bool colision_artefacto;
        bool colision_enemigo;
        int ataque;
        int gemas;
        int plantas;
        bool attack_on;
        
};

class  Enemigo : public ObjetoDinamico
{
    public:
        virtual ~Enemigo(){};
        Enemigo(float vida, int x, int y,SDL_Color c );
        Enemigo(std::string path_sprite,float vida,int ataque, int x, int y, int w, int h,int sw,int sh, SDL_Color c );
          Enemigo(std::string path_sprite,float vida,int ataque, int x, int y, int w, int h,int sw,int sh, SDL_Color c, Jugador* objeto_seguir);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};

        void set_estado(void* estado);
        void* get_estado();

        void set_size(Coordenadas size){this->size = size;};
        Coordenadas get_size(){return size;};

        void set_ataque(int ataque){this->ataque = ataque;};
        int get_ataque(){return ataque;};


        void lock_objeto(Objeto &obj);
        void unluck_objeto();
        Objeto* get_obj_lock()const{return objeto_seguir;};
        void set_Objeto_seguir(Objeto* obj){objeto_seguir = obj;};

        Jugador* get_jugador_seguir()const{return jugador_seguir;};
        void set_jugador_seguir(Jugador* obj){jugador_seguir = obj;};

      


        int lock{0};
        float velocidad;
        int en_transicion{0};
        int width, height;
        bool start;

       // void checar_colisiones();
    private:
        FSMEnemigo* estado_actual;
        Coordenadas piso;
        Coordenadas size;
        int ataque;
        Objeto* objeto_seguir;
         Jugador* jugador_seguir;
        
    
};

class  Guardian : public ObjetoDinamico
{
    public:
        virtual ~Guardian(){};
        Guardian(float vida, int x, int y,SDL_Color c );
        Guardian(std::string path_sprite,float vida,int ataque, int x, int y, int w, int h,int sw,int sh, SDL_Color c );
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};

        void set_estado(void* estado);
        void* get_estado();

        void set_size(Coordenadas size){this->size = size;};
        Coordenadas get_size(){return size;};

        void set_ataque(int ataque){this->ataque = ataque;};
        int get_ataque(){return ataque;};

        float get_velocidad(){return velocidad;};

        void lock_objeto(Objeto &obj);
        void unluck_objeto();
        Objeto* get_obj_lock()const{return objeto_seguir;};

        void set_first_time(int first_time){this->first_time = first_time;};
        int get_first_time(){return first_time;};


        int lock{0};
        float velocidad;
        int en_transicion{0};

       // void checar_colisiones();
    private:
        FSMGuardian* estado_actual;
        Coordenadas piso;
        Coordenadas size;
        int ataque;
        Objeto* objeto_seguir;
        int first_time;
};