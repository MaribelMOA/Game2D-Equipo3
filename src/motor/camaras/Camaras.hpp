#pragma once
#include "../../utilidad/Estructuras.hpp"
#include "../../objetos/Objeto.hpp"
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../objetos/Figuras.hpp"
#include "../Pipeline.hpp"
#include "../KeyOyente.hpp"
#include "../MouseOyente.hpp"
#include "../../utilidad/FSMS/FSMCamaras.hpp"

#include <SDL.h>
#include <vector>

class FSMCamara; //declaración circular

class Camara
{
    public:
        Camara(int x, int y, int w, int h, SDL_Renderer &view);
        Camara(int x, int y, int w, int h, Objeto *en,SDL_Renderer &view);
        ~Camara();
        void renderizar(std::vector<Objeto*> objetos);
        void proyectar(std::vector<Objeto*> objetos);
        void render_cross();

        Coordenadas get_posicion_mundo() const {return pos_mundo;};
        void set_posicion_mundo(Coordenadas np);
        void set_posicion_centro(Coordenadas np);
        Coordenadas get_posicion_centro() const{return pos_centro;};

        void lock_objeto(Objeto &obj);
        void unluck_objeto();
        Objeto* get_obj_lock()const{return objeto_seguir;};
        void set_monstruo(Objeto* m){monstruo=m;};
        Objeto* get_monstruo()const{return monstruo;};

        void set_limites(std::vector<Coordenadas> l){limites=l;};
        std::vector<Coordenadas> get_limites()const{return limites;};

        void checar_pos_jugador();

        //bool free_zone(&);

        /*FSM métodos*/
        void input_handle(KeyOyente &input, MouseOyente &mouse);
        void update();
    
    public:
        int lock{0};
        float velocidad;
        int en_transicion{0};
        bool en_colision;
        bool game_over;
        bool start;
    
    private:
        int width;
        int height;
        Coordenadas pos_mundo;
        Coordenadas pos_centro;
        SDL_Renderer *viewport;
        Pipeline * objensamble;
        std::vector<Coordenadas> cruz;
        std::vector<Coordenadas> limder;
        std::vector<Coordenadas> limizq;
        Objeto* objeto_seguir,*jugador;
        FSMCamara* estado_actual;
        
        Objeto* monstruo;
        std::vector<Coordenadas> limites;
};