#include "Pipeline.hpp"
#include "Plotter.hpp"

#define RELLENO 0

Pipeline::Pipeline(SDL_Renderer &ren)
{
    ptrren = &ren;
};

void Pipeline::puntos(std::vector<Coordenadas> p,SDL_Color c)
{
    //cada p es un punto en el espacio, simplemente llamar a plotter para pintarlos
    for(auto &punto:p)
        Plotter::get().render_pixel(ptrren,punto,c);
};

void Pipeline::lineas(std::vector<Coordenadas> p,SDL_Color c)
{
    // asumiendo p1-p2, p3-p4, ... ,pn-1-pn
    int size =  p.size();
    for(int i=0; i<size;i+=2)
    {
        Plotter::get().render_linea(ptrren,p[i],p[(i+1)%size],c);
    }
};

void Pipeline::figuras(std::vector<Figura*> f)
{
    // asumiendo que las lineas de la figuras estan p1-p2-p3-loop
    for(auto &fig : f)
    {
        #if RELLENO == 0
        //primero rellenamos para tapar imperfectos
        if(fig->get_serellena())
            Plotter::get().rellenoscandline(ptrren,fig);
        #endif

        //luego los contornos
        int size = fig->get_vertices().size();
        std::vector<Coordenadas> vertices = fig->get_vertices();
        for(int j=0;j<size;j++)
        {
            Plotter::get().render_linea(ptrren,vertices[j],vertices[(j+1)%size],fig->get_strokecolor());
        }
    }
};
void Pipeline::figuras(Figura* f)
{
    
    #if RELLENO == 0
    //primero rellenamos para tapar imperfectos
    if(f->get_serellena())
        Plotter::get().rellenoscandline(ptrren,f);
    #endif

    //luego los contornos
    int size = f->get_vertices().size();
    std::vector<Coordenadas> vertices = f->get_vertices();
    for(int j=0;j<size;j++)
    {
        Plotter::get().render_linea(ptrren,vertices[j],vertices[(j+1)%size],f->get_strokecolor());
    }
};

void Pipeline::pintar_texturas(Sprite *obj)
{
    Plotter::get().pintar_textura(ptrren,obj->get_textura(),*obj->get_sprite_src(),*obj->get_sprite_frame(),obj->get_sprite_sizes());
    
};
void Pipeline::pintar_texturas(Tile *obj)
{
    Plotter::get().pintar_textura(ptrren,obj->get_textura(),*obj->get_src(),*obj->get_dst(),obj->get_sizes());
};

bool Pipeline::cargar_texturas(Sprite *obj)
{
    //si no existe regresa flase, y si existe regresa true
    
    return obj->cargar_textura(ptrren);
};
