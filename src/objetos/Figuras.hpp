#pragma once

#include<vector>
#include "../utilidad/Estructuras.hpp"
#include<SDL.h>

class Figura
{
    public:
        virtual ~Figura(){};
        Coordenadas get_posicion() const {return posicion;};
        void set_position(int x, int y){posicion.x=x;posicion.y=y;};
        std::vector<Coordenadas> get_vertices() const {return vertices;};
        void set_vertices(std::vector<Coordenadas> nv){vertices=nv;};
        void set_strokecolor(SDL_Color nc){lineacolor=nc;};
        SDL_Color get_strokecolor() const {return lineacolor;};
        void set_rellenocolor(SDL_Color nc){rellenocolor=nc;};
        SDL_Color get_rellenocolor()const {return rellenocolor;};
        Coordenadas get_pivote() const{return pivote;};
        bool get_serellena() const{return se_rellena;};
        void set_serellena(bool v){se_rellena=v;};
        //interface
        virtual void generar_vertices()=0;
        virtual void update_vertices()=0;

    protected:
        std::vector<Coordenadas> vertices;
        Coordenadas posicion;
        SDL_Color lineacolor;
        SDL_Color rellenocolor;
        Coordenadas pivote;
        bool se_rellena;
};

class Rectangulo : public Figura
{
    public:
        Rectangulo(int x, int y, int w, int h,SDL_Color color);
        virtual ~Rectangulo(){};

        void generar_vertices();
        void update_vertices();
    private:
        int width;
        int height;

};

class Triangulo : public Figura
{
    public:
        Triangulo(Coordenadas p1,Coordenadas p2,Coordenadas p3,SDL_Color color);
        //Triangulo(int x,int y,int w, int h, SDL_Color color);
        virtual ~Triangulo(){};

        void generar_vertices();
        void update_vertices();
    private:
        Coordenadas A;
        Coordenadas B;
        Coordenadas C;

};

class Circulo : public Figura
{
    public:
        Circulo(int r,int x,int y,int numvertices, SDL_Color color);
        virtual ~Circulo(){};

        void generar_vertices();
        void update_vertices();
    private:
        int radio;
        int segmentos;

};