#include "Figuras.hpp"
#define PI 3.141592653589793

/*Rectángulo*/
Rectangulo::Rectangulo(int x, int y, int w, int h,SDL_Color color)
{
    pivote = Coordenadas{x,y};
    posicion = Coordenadas{x,y};
    lineacolor = color;
    width =w;
    height=h;
    this->generar_vertices();
    se_rellena=true;
};

void Rectangulo::generar_vertices()
{
    //pivote [top lef] move to right
    /*   
    vertices.push_back({posicion.x,posicion.y});
    vertices.push_back({posicion.x+width,posicion.y});
    vertices.push_back({posicion.x+width,posicion.y+height});
    vertices.push_back({posicion.x,posicion.y+height});
    */
    //pivote [centro] A--D--C--B--A
    vertices.push_back({posicion.x-width/2,posicion.y-height/2}); //a
    vertices.push_back({posicion.x-width/2,posicion.y+height/2}); //d
    vertices.push_back({posicion.x+width/2,posicion.y+height/2}); //c
    vertices.push_back({posicion.x+width/2,posicion.y-height/2}); //b
    
    
};

void Rectangulo::update_vertices()
{
    //ajustar los vertices
    vertices[0] = {posicion.x-width/2,posicion.y-height/2};
    vertices[1] = {posicion.x-width/2,posicion.y+height/2};
    vertices[2] = {posicion.x+width/2,posicion.y+height/2};
    vertices[3] = {posicion.x+width/2,posicion.y-height/2};
    
    

};

/*Triángulo*/

Triangulo::Triangulo(Coordenadas p1, Coordenadas p2, Coordenadas p3, SDL_Color color)
{
    // de L to R
    posicion = p1;
    pivote = p1;
    A = p1;
    B = p2;
    C = p3;
    lineacolor = color;
    this->generar_vertices();
    se_rellena=true;
};

void Triangulo::generar_vertices()
{
    //A-B
    vertices.push_back(A);
    vertices.push_back(B);
    vertices.push_back(C);
};

void Triangulo::update_vertices()
{
    vertices[0] = A;
    vertices[1] = B;
    vertices[2] = C;

};

/*Círculo*/
Circulo::Circulo(int r,int x, int y, int numvertices,SDL_Color color)
{
    radio = r;
    segmentos = numvertices;
    posicion = Coordenadas{x,y};
    lineacolor = color;
    this->generar_vertices();
    se_rellena=true;
}

void Circulo::generar_vertices()
{
  /*Forma trigonometrica*/
    for(int i=0; i<segmentos;++i)
    {
        float angulo = i* (2*PI) /segmentos; //2*angulo de 360°
        int x = posicion.x+SDL_cos(angulo)*radio;
        int y = posicion.y+SDL_sin(angulo)*radio;
        vertices.push_back({x,y});
    }
    
/*
    int rr= radio*radio;
    for(int x = -radio;x<=radio;++x)
    {
        int hh = (int)(SDL_sqrt(rr-x*x)+0);
        int cyy = x+posicion.y;
        vertices.push_back({posicion.x-hh,cyy});
        vertices.push_back({posicion.x+hh,cyy});
    }
*/
    //printf("Se creo circulo con %ld vertices\n",vertices.size());
};

void Circulo::update_vertices()
{

};