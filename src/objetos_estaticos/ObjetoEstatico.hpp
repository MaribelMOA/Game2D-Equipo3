#pragma once
#include "../objetos/Objeto.hpp"
#include "../utilidad/Estructuras.hpp"
#include "../motor/imagen/tiles.hpp"
#include <SDL.h>

class ObjetoEstatico : public Objeto
{
    public:
        virtual ~ObjetoEstatico(){};
        virtual void update(double dt) = 0;
        virtual void set_ID(int ID)=0;
       virtual  int get_ID()=0;
    private:
        int ID_tile;

};

class Plataformas : public ObjetoEstatico
{
    public:
        virtual ~Plataformas(){};
        Plataformas(int x, int y, int w, int h, SDL_Color color);
        Plataformas(TileInfo tiles,bool colision,int ID);
        void update(double dt);
        void set_ID(int ID){this->ID_tile=ID;};
        int get_ID(){return ID_tile;};
        void set_tile(TileInfo tilein){this->tilein=tilein;};
        TileInfo get_tilein(){return tilein;};
    private:
        int ID_tile;
        TileInfo tilein;

    
};

