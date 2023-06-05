#include "Plotter.hpp"
#include "../utilidad/Func_aux.hpp"
#include<iostream>

//#define MOSTRARDEBUG
#define LINEASBRESSENHAM

Plotter* Plotter::instancia =0;

Plotter::Plotter(){/*nada que inicializar*/};

//singleton
Plotter& Plotter::get()
{
    if(!instancia)
        instancia = new Plotter();
    return *instancia;
};

void Plotter::render_pixel(SDL_Renderer *r, Coordenadas p, SDL_Color color)
{
    //designar como utilizar el alpha
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    //asignar el color
    SDL_SetRenderDrawColor(r,color.r,color.g,color.b,color.a);
    //pintar el pixel
    SDL_RenderDrawPoint(r,p.x,p.y); 
    
};

void Plotter::render_linea(SDL_Renderer *r, Coordenadas p1, Coordenadas p2,SDL_Color color)
{
    //Implementar usando el algoritmo BRESSENHAM y el render_pixel
    // NO USAR SDL_RenderDrawLine
    #ifdef LINEASBRESSENHAM
    int dx = std::abs(p2.x-p1.x);
    int sx = (p1.x<p2.x) ? 1:-1;
    int dy = -std::abs(p2.y-p1.y);
    int sy = (p1.y<p2.y) ? 1:-1;
    int error = dx+dy;

    int nx = p1.x;
    int ny = p1.y;

    while(true)
    {
        Plotter::get().render_pixel(r,{nx,ny},color);
        if(nx== p2.x && ny == p2.y){ break;}
        int e2 = 2*error;
        if(e2 >=dy)
        {
            if(nx == p2.x) {break;}
            error +=dy;
            nx+=sx;
        }
        if(e2<=dx)
        {
            if(ny==p2.y){ break;}
            error+=dx;
            ny+=sy;
        }
    }
    #else
    float diff =0.015; //10 puntos por linea(1/diff)
    float u= 0; // de 0 a 1 
    while(u<=1) 
    {
        Coordenadas pix = LERP(p1,p2,u);
        get().render_pixel(r,pix,color);
        u+=diff;
    }
    #endif 
};


void Plotter::rellenoscandline(SDL_Renderer *r,Figura* fig)
{
    std::vector<Coordenadas> vertices = fig->get_vertices();
    int xmin = coordenada_minima(vertices,'x');
    int xmax = coordenada_maxima(vertices,'x');
    int ymin = coordenada_minima(vertices,'y');
    int ymax = coordenada_maxima(vertices,'y');
    int numvert = fig->get_vertices().size();
    

    //de ymin hasta ymax
    std::vector<Coordenadas> inter;
    for(int y=ymin+1;y<ymax;++y)
    {
        for(int i=0;i<numvert;++i)
        {
            bool td= tiene_determinante({xmin,y},{xmax,y},vertices[i],vertices[(i+1)%numvert]);
            if(td)
            {
                Coordenadas ip = interseccion({xmin,y},{xmax,y},vertices[i],vertices[(i+1)%numvert]);
                if(!(ip.x<xmin || ip.x>xmax) && !(ip.y< ymin || ip.y>ymax))
                {
                    inter.push_back(ip);
                }
            }
        }
    }
    // ordenar en las ejes de la x
    inter = wrapper_sort(inter,'x',sort_insertion);

    #ifdef MOSTRARDEBUG
    printf("xmin: %d xmax: %d ymin: %d ymax: %d\n",xmin,xmax,ymin,ymax);
    for(int v=0;v<(int)inter.size()/2;++v)
        DEBUGLINEA(inter[inter.size()-v-1],inter[v]);
    #endif

    //pintar
    int isize=inter.size();
    for(int v=0;v<isize/2;++v)
        get().render_linea(r,inter[isize-v-1],inter[v],fig->get_rellenocolor());
};

void Plotter::pintar_textura(SDL_Renderer *r,SDL_Texture *textura,SDL_Rect &src , SDL_Rect &dest, Coordenadas size)
{
    //copia imagen en una textura
    //null en el W Y H gata el tamano de la textura
    //pero provoca escalamiento sin antialias
    //SI LA IMAGEN ES MUY GRANDE Y LA HACES CHIQUTA HABRA ARTEFACTOS EN LAS ORILLAS. si ES AL REVEZ, SE PUEDE VER BOROSA
    SDL_QueryTexture(textura,NULL,NULL,NULL,NULL);
    //escalamiento y pintamos en pantalla
    dest.w = size.x;
    dest.h = size.y;
    SDL_RenderCopy(r,textura,&src,&dest);
    //SI QUIEREN QUE LA TEXTURA SE FLIPE, OUEDEN 
   // LO QUE PUSO EN LA PRESENTACION
   
};