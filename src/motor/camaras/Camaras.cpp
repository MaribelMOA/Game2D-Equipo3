#include "Camaras.hpp"
#include "../../utilidad/Func_aux.hpp"
#include <iostream>

Camara::Camara(int x, int y, int w, int h, SDL_Renderer &view)
{
    // se considera que la camara empieza en 0,0 y es toda la pantalla
    // si se quiere centrar hay que desplazar w y h en todos los cálculos.
      width =w;
    height=h;
    pos_mundo = {x,y};
    pos_centro = {x+w/2,y+h/2};

    cruz.push_back({x,y+h/2});
    cruz.push_back({x+w,y+h/2});
    cruz.push_back({x+w/2,y});
    cruz.push_back({x+w/2,y+h});

    limites.push_back({x+((3*w)/8),y+((3*h)/8)});
    limites.push_back({x+((6*w)/8),y+((6*h)/8)});

   // monstruo->set_posicion_mundo({x+w/2,y+h/2});
    viewport = &view;
    objensamble = new Pipeline(view);
    velocidad =50.f;
    estado_actual = new EstadoCamaraMover({0,0});
    game_over = false;
    start = false;


};

Camara::Camara(int x, int y, int w, int h, Objeto * en,SDL_Renderer &view)
{
    // se considera que la camara empieza en 0,0 y es toda la pantalla
    // si se quiere centrar hay que desplazar w y h en todos los cálculos.
    width =w;
    height=h;
    pos_mundo = {x,y};
    pos_centro = {x+w/2,y+h/2};

    cruz.push_back({x,y+h/2});
    cruz.push_back({x+w,y+h/2});
    cruz.push_back({x+w/2,y});
    cruz.push_back({x+w/2,y+h});

 limites.push_back({x+((3*w)/8),y+((3*h)/8)});
    limites.push_back({x+((6*w)/8),y+((6*h)/8)});

    monstruo = en;
   // monstruo->set_posicion_mundo({x+w/2,y+h/2});
    viewport = &view;
    objensamble = new Pipeline(view);
    velocidad =35.f;
    estado_actual = new EstadoCamaraMover({0,0});
    game_over = false;
    start = false;
};

Camara::~Camara()
{
    SDL_DestroyRenderer(viewport);
    delete objensamble;
    delete estado_actual;
    delete objeto_seguir;
};

void Camara::render_cross()
{
    objensamble->lineas(cruz,{0,255,0,180});
};

void Camara::lock_objeto(Objeto &obj)
{
    //Alumnos implementarla
    objeto_seguir = &obj;
    lock =1;
    
};

void Camara::unluck_objeto()
{
    //Alumnos implementarla
    objeto_seguir = nullptr;
    lock=0;
};

void Camara::proyectar(std::vector<Objeto*> objetos)
{
    //Alumnos implementarla 
    for(auto &o:objetos)
    {
        Coordenadas posM = o->get_posicion_mundo();
        posM.x -=pos_mundo.x;
        posM.y -=pos_mundo.y;
        o->set_posicion_mundo(posM);
        //DEBUGCOOR(posM)
    }
    //DEBUGPRINT("_____")
    
};

void Camara::renderizar(std::vector<Objeto*>objetos)
{
    for(auto& o:objetos)
    {
        o->render(viewport);
    }
};

void Camara::set_posicion_mundo(Coordenadas np)
{
    pos_mundo = np;
};
void Camara::set_posicion_centro(Coordenadas np)
{
    pos_centro = np;
};


void Camara::input_handle(KeyOyente &input, MouseOyente &mouse)
{
    if(!estado_actual)
        return; //estado nulo al inicio
    
    FSMCamara* estado = estado_actual->input_handle(*this,input,mouse);
    if(estado)
    {
        estado_actual->on_salir(*this);
        delete estado_actual;
        estado_actual = estado;
        estado_actual->on_entrar(*this);
    }
};

void Camara::update()
{
    if(start==true) checar_pos_jugador();
    if(estado_actual)
        estado_actual->on_update(*this);
   
};

void Camara::checar_pos_jugador(){
    int x1=limites.at(0).x;
    int x2=limites.at(1).x;
    int y1=limites.at(0).y;
    int y2=limites.at(1).y;

    int posXObjeto = get_obj_lock()->get_posicion_mundo().x;
    int posYObjeto = get_obj_lock()->get_posicion_mundo().y;
    if(posXObjeto<x1 || posXObjeto>x2 || posYObjeto<y1 || posYObjeto>y2)
    {
        if(lock==0){
           // lock_objeto(*jugador);
        //cam.lock=1;
            lock=1;
           // printf("lock\n");
        }
       
    }else{
        if(lock==1){
            jugador=objeto_seguir;
            //printf("unlock\n");
            //unluck_objeto();
            lock=0;
        }
        
    }
    

}